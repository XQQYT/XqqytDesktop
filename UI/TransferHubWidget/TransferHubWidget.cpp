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
 #include "EventBus.h"
 #include "GlobalEnum.h"
 
 TransferHubWidget::TransferHubWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransferHubWidget)
 {
    ui->setupUi(this);
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
   //接收到远端添加文件
   EventBus::getInstance().subscribe(EventBus::EventType::WebRTC_SyncAddFile,[=](std::string id, std::string filename, std::string file_size){
      QMetaObject::invokeMethod(this, [=]() {
         addFile(true,QString::fromStdString(filename), std::stoi(id), std::stoul(file_size));
         moveToShown();
         hideTimer->start();
      }, Qt::QueuedConnection);
      
   });
}
 
TransferHubWidget::~TransferHubWidget()
{
   delete ui;
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
void TransferHubWidget::addFile(bool is_remote,QString detail,unsigned int input_file_id, size_t file_size)
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

   connect(item,&FileItemWidget::fileItemDelete,this,&TransferHubWidget::onDeleteFileItem);     
   
   existing_etails.insert(detail);
   std::vector<std::string> args = {std::to_string(item->fileid - 1), item->file_name.toStdString(), std::to_string(item->file_size)};
   if(!is_remote)
      EventBus::getInstance().publish(EventBus::EventType::WebRTC_SyncFileInfo, FileSyncType::ADDFILE,  std::move(args));
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