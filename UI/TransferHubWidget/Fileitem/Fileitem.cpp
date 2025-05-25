#include "Fileitem.h"
#include <QDirIterator>
#include <iostream>
#include <QDebug>
#include <QMenu>
#include <QClipboard>
#include <QDesktopServices>
#include <QMessageBox>
#include "UserInfo.h"
#include "EventBus.h"
#include "GlobalEnum.h"

uint16_t FileItemWidget::fileid = 0; 
static const QString tmp_path = "/tmp/XqqytDesktop/";

quint64 getFolderSize(const QString &folderPath)
{
    quint64 totalSize = 0;
    QDirIterator it(folderPath,
                    QDir::Files | QDir::NoSymLinks,
                    QDirIterator::Subdirectories);

    while (it.hasNext()) {
        it.next();
        QFileInfo fileInfo = it.fileInfo();
        totalSize += fileInfo.size();
    }

    return totalSize;
}

QIcon FileItemWidget::getIcon(const QString& path)
{
    QIcon fileIcon;
    QFileInfo file_info(path);
    if(file_info.isDir())
    {
        fileIcon = provider.icon(QFileIconProvider::Folder);
        file_size = getFolderSize(path);
    }
    else
    {
        fileIcon = provider.icon(QFileInfo(path));
        file_size = file_info.size();
    }
    file_name = file_info.fileName();
    return fileIcon;
}

FileItemWidget::FileItemWidget(bool is_remote,QString& detail,uint16_t input_file_id, size_t file_size,QWidget *parent)
    : QWidget(parent),is_remote(is_remote) ,detail(detail)
{
    //被控端从1000开始编号
    if (fileid == 0 && UserInfoManager::getInstance().getCurrentRole() == UserInfoManager::Role::BeControlled) {
        fileid = 1000;
    }

    iconLabel = new QLabel;
    iconLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    textLabel = new QLabel(this);
    textLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    textLabel->setWordWrap(true);  

    auto *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->addWidget(iconLabel);
    layout->addWidget(textLabel);

    if(!is_remote)
    {
        iconLabel->setPixmap(getIcon(detail).pixmap(64, 64));
        textLabel->setText(file_name);
        file_id = fileid++;
    }
    else
    {
        iconLabel->setPixmap(QIcon(":/images/pic/remote_file.png").pixmap(64, 64));
        this->file_size = file_size;
        textLabel->setText(detail);
        file_id = input_file_id;
    }

    setCursor(Qt::OpenHandCursor);
    setFixedSize(120, 120);
    setToolTip(
        "<b>FileName:</b> " + file_name +
        "<br><b>Size:</b> " + QString::number(this->file_size) + " bytes" + 
        "<br><b>id:</b> " + QString::number(file_id)
    );
    
    setStyleSheet("QToolTip { color: white; background-color: rgba(80, 80, 80, 255); }");

}

// 鼠标按下时记录起始点
void FileItemWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        dragStartPosition = event->pos();
}

// 鼠标移动距离超过阈值后触发拖动
// void FileItemWidget::mouseMoveEvent(QMouseEvent *event) {
//     if (!(event->buttons() & Qt::LeftButton)) return;
//     if ((event->pos() - dragStartPosition).manhattanLength() < QApplication::startDragDistance()) return;

//     QString absolutePath = QFileInfo(detail).absoluteFilePath();

//     QMimeData *mimeData = new QMimeData;
//     QUrl fileUrl = QUrl::fromLocalFile(absolutePath);
    
//     // Qt 有时自动推导不完全，手动设置
//     mimeData->setUrls({fileUrl});
//     mimeData->setData("text/uri-list", fileUrl.toEncoded());  // 👈 Nautilus 要求这个！
    
//     QDrag *drag = new QDrag(this);  // this 是你的 FileItemWidget
//     drag->setMimeData(mimeData);
//     drag->setPixmap(*iconLabel->pixmap());
//     drag->setHotSpot(event->pos());
    
//     Qt::DropAction result = drag->exec(Qt::CopyAction);
//     if (result == Qt::MoveAction) {
//         qDebug() << "文件被移动（剪切）";
//     } else if (result == Qt::CopyAction) {
//         qDebug() << "文件被复制";
//     } else {
//         qDebug() << "拖拽取消或失败";
//     }
// }

void FileItemWidget::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    menu.setStyleSheet(R"(
        QMenu {
            background-color:rgb(157, 154, 154);
            color: white;
        }
        QMenu::item {
            padding: 5px 25px;
            background-color: transparent;
        }
        QMenu::item:selected {
            background-color: #444;
        }
    )");
    
    QAction *copyAction = menu.addAction("复制");
    QAction *openAction = menu.addAction("打开");
    QAction *deleteAction = menu.addAction("删除");

    QAction *selectedAction = menu.exec(event->globalPos());

    if (selectedAction == copyAction) {
        onCopy();
    } else if (selectedAction == openAction) {
        onOpen();
    } else if (selectedAction == deleteAction) {
        onDelete();
    }else{

    }
}

void FileItemWidget::onCopy()
{
    QClipboard *clipboard = QApplication::clipboard();
    QMimeData *mimeData = new QMimeData;
    QUrl fileUrl;
    if(is_remote)
    {
        fileUrl = QUrl::fromLocalFile(QFileInfo(tmp_path + detail).absoluteFilePath());
    }
    else
    {
        fileUrl = QUrl::fromLocalFile(QFileInfo(detail).absoluteFilePath());
    }
    mimeData->setUrls({fileUrl});
    mimeData->setData("x-special/gnome-copied-files", QByteArray("copy\n") + fileUrl.toEncoded());

    clipboard->setMimeData(mimeData);

}

void FileItemWidget::onOpen()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(detail));
}

void FileItemWidget::onDelete()
{
    emit fileItemDelete(this);
}
void FileItemWidget::mouseMoveEvent(QMouseEvent *event) {
    event->ignore();
}