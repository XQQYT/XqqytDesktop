/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

 #include "TransferHubWidget.h"
 #include "ui_TransferHubWidget.h"
 #include <QScreen>
 #include <QApplication>
 #include <QPropertyAnimation>
 #include <QTimer>
 #include <QPushButton>
 #include <QPainter>
 #include <QDir>
 #include "EventBus.h"
 #include "GlobalEnum.h"
 #include "TransferFiles.h"
 
 static const QString tmp_path = "/tmp/XqqytDesktop/";

 void createLocalFile(QString filename) {
   QFile file(tmp_path+filename);

   if (file.open(QIODevice::WriteOnly)) {
       file.close();
   }
}

 TransferHubWidget::TransferHubWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransferHubWidget)
 {
    ui->setupUi(this);

    current_receive_file_id = UINT16_MAX;
    QDir dir(tmp_path);
    if(!dir.exists())
      dir.mkdir(tmp_path);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);

    setAcceptDrops(true);

    setFixedHeight(160);
    
   scrollArea = new RoundedScrollArea(this);
   scrollArea->setFrameShape(QFrame::NoFrame);
   scrollArea->setWidgetResizable(true);
   scrollArea->setAttribute(Qt::WA_TranslucentBackground);
   scrollArea->setStyleSheet("QScrollArea { background: transparent; }");

   QWidget *scroll_container = new QWidget;
   scroll_container->setAttribute(Qt::WA_TranslucentBackground);
   scroll_container->setStyleSheet("background: transparent;");

   QWidget *container = new QWidget;
   gridLayout = new QGridLayout(container);
   gridLayout->setContentsMargins(20, 0, 20, 0);
   container->setLayout(gridLayout);
   scrollArea->setWidget(container);
   scrollArea->setWidgetResizable(true);

   ui->gridLayout_2->addWidget(scrollArea);
   gridLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

   hideTimer = new QTimer(this);

   hideTimer->setInterval(1200);
   connect(hideTimer, &QTimer::timeout, this, [=](){
      hide();
   });
   
   QScreen *screen = QGuiApplication::primaryScreen();
   if (!screen) return;

   QRect screenGeometry = screen->availableGeometry();
   init_x = (screenGeometry.width() - width()) / 2;
   init_y = 0;

   move(init_x, init_y);

   hoverTimer = new QTimer(this);
   hoverTimer->setInterval(100);

   connect(hoverTimer, &QTimer::timeout, this, [=]() {
       QPoint globalPos = QCursor::pos();
       QScreen *screen = QGuiApplication::primaryScreen();
       QRect screenGeometry = screen->availableGeometry();

       QRect hoverZone((screenGeometry.width() - width()) / 2,
                       0,
                       width(),
                       50);

       if (hoverZone.contains(globalPos)) {
           moveToShown();
       } 
   });

   EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_ReceiveFileProgess, [=]
      (uint16_t id, uint32_t receive_size, uint32_t totale_size)
      {
          uint16_t progress = static_cast<uint16_t>((static_cast<uint64_t>(receive_size) * 100) / totale_size);
          id_file[id]->setProgress(progress);
          if(receive_size >= totale_size)
          {
            if(!receive_file_queue.empty())
            {
               current_receive_file_id = UINT16_MAX;
               receive_file_queue.pop();
               QMetaObject::invokeMethod(this, [=]() {
               prepareNextReceiveFile();
               });
            }
          }
         });

   //接收到远端添加文件
   EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_SyncAddFile,[=](std::string id, std::string filename, std::string file_size){
      QMetaObject::invokeMethod(this, [=]() {
         addFile(true,QString::fromStdString(filename), std::stoi(id), std::stoul(file_size));
         moveToShown();
         hideTimer->start();
      }, Qt::QueuedConnection);
      createLocalFile(QString::fromStdString(filename));
      receive_file_queue.push({std::stoi(id),filename});
      if(current_receive_file_id == UINT16_MAX)
      {
         QUrl fileUrl = QUrl::fromLocalFile(QFileInfo(tmp_path + QString::fromStdString(filename)).absoluteFilePath());
         current_file_stream = std::make_shared<std::ofstream>((tmp_path + QString::fromStdString(filename)).toStdString(), std::ios::binary);
   
         EventBus::getInstance().publish<std::shared_ptr<std::ofstream>, std::function<void()>>(EventBus::EventType::WebRTC_SetFileHolder, current_file_stream,
            [=](){
            std::vector<std::string> args = {id};
            EventBus::getInstance().publish(EventBus::EventType::WebRTC_SyncFileInfo, FileSyncType::GETFILE,std::move(args));
         });
         current_receive_file_id = receive_file_queue.front().first;
      }
   });

}
 
TransferHubWidget::~TransferHubWidget()
{
   delete ui;
}

void TransferHubWidget::prepareNextReceiveFile()
{
    if (!receive_file_queue.empty())
    {
        auto next_file = receive_file_queue.front(); // 复制

        QString filePath = tmp_path + QString::fromStdString(next_file.second);
        current_file_stream = std::make_shared<std::ofstream>(filePath.toStdString(), std::ios::binary);
         std::cout<<current_file_stream.get()<<std::endl;
        if (!current_file_stream->is_open()) {
            std::cerr << "Error: Failed to open file for writing: " << filePath.toStdString() << std::endl;
            return;
        }

        // 发布文件接收准备事件
        EventBus::getInstance().publish<std::shared_ptr<std::ofstream>, std::function<void()>>(
            EventBus::EventType::WebRTC_SetFileHolder,
            current_file_stream,
            [next_file]() {
                std::vector<std::string> args = { std::to_string(next_file.first) };
                EventBus::getInstance().publish(EventBus::EventType::WebRTC_SyncFileInfo, FileSyncType::GETFILE, std::move(args));
            }
        );

        current_receive_file_id = next_file.first;
    }
    else
    {
        current_file_stream.reset();
    }
}
 
void TransferHubWidget::moveToShown()
{
   move(init_x, init_y);
   show();
}
 
void TransferHubWidget::paintEvent(QPaintEvent *event)
{
   Q_UNUSED(event);
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing);
   QColor bgColor(255, 255, 255, static_cast<int>(0.6 * 255));
   painter.setBrush(bgColor);
   painter.setPen(Qt::NoPen);
   painter.drawRoundedRect(rect(), 20, 20);
}

void TransferHubWidget::enterEvent(QEvent *event)
{
   if(hideTimer->isActive())
      hideTimer->stop();
}

void TransferHubWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);

    if (QApplication::activePopupWidget() != nullptr) {
        return;
    }

    hideTimer->start();
}
 
//本地文件只需传is remote和detail(文件路径)，剩余信息会在file item中读路径获取,detail解析后显示文件名
//远程文件需要填全，detail则为文件名直接显示
void TransferHubWidget::addFile(bool is_remote,QString detail,uint16_t input_file_id, size_t file_size)
{
   if(existing_etails.contains(detail))
   {
      return;
   }

   int row = cur_count / colCount;
   int col = cur_count % colCount;

   auto *item = new FileItemWidget(is_remote,detail,input_file_id, file_size);
   gridLayout->addWidget(item, row, col);

   cur_count++;

   file_items.append(item);
   id_file.insert(item->getID(),item);

   connect(item,&FileItemWidget::fileItemDelete,this,&TransferHubWidget::onDeleteFileItem);     
   
   existing_etails.insert(detail);
   
   if(!is_remote)
   {
      TransferFilesManager::getInstance().addFileInfo(item->fileid - 1, detail.toStdString());
      std::vector<std::string> args = {std::to_string(item->fileid - 1), item->file_name.toStdString(), std::to_string(item->file_size)};
      EventBus::getInstance().publish(EventBus::EventType::WebRTC_SyncFileInfo, FileSyncType::ADDFILE,  std::move(args));
   }
}

void TransferHubWidget::start()
{
   if(hoverTimer->isActive())
      hoverTimer->stop();
   hoverTimer->start();
}

void TransferHubWidget::stop()
{
   if(hoverTimer->isActive())
      hoverTimer->stop();
}

void TransferHubWidget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
        if (hideTimer->isActive())
            hideTimer->stop();
    }
}

void TransferHubWidget::dropEvent(QDropEvent *event)
{
    const QList<QUrl> urls = event->mimeData()->urls();
    for (const QUrl &url : urls)
    {
        QString localPath = url.toLocalFile();
        if (!localPath.isEmpty())
        {
            addFile(false, std::move(localPath));
        }
    }

    hideTimer->start();
}

void TransferHubWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    Q_UNUSED(event);
    hideTimer->start();
}

void clearLayout(QLayout* layout)
{
    if (!layout) return;
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        layout->removeItem(item); // 移除布局项（如果不调用 delete）
    }
}

void TransferHubWidget::onDeleteFileItem(FileItemWidget* item)
{
   id_file.remove(item->getID());
   file_items.removeOne(item);
   existing_etails.remove(item->detail);
   gridLayout->removeWidget(item);
   item->deleteLater();

   clearLayout(gridLayout);

   cur_count = 0;

   for (auto& i : file_items)
   {
      int row = cur_count / colCount;
      int col = cur_count % colCount;
      gridLayout->addWidget(i, row, col);
      cur_count++;
   }
}

void TransferHubWidget::reset()
{
    if (current_file_stream && current_file_stream->is_open()) {
        current_file_stream->close();
    }
    current_file_stream.reset();

    current_receive_file_id = UINT16_MAX;

    // 清空接收队列
    std::queue<std::pair<uint16_t, std::string>> empty;
    std::swap(receive_file_queue, empty);

    // 清空UI中的文件项
    for (auto& item : file_items) {
        id_file.remove(item->getID());
        item->deleteLater();
    }
    file_items.clear();
    existing_etails.clear();

    clearLayout(gridLayout);
    cur_count = 0;

    std::cout << "TransferHubWidget has been reset." << std::endl;
}