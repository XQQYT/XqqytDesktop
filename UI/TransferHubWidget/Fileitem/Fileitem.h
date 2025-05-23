#ifndef _FILEITEM_H
#define _FILEITEM_H

#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QVBoxLayout>
#include <QIcon>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QFileIconProvider>
#include <QFileInfo>

class FileItemWidget : public QWidget {
    Q_OBJECT
public:
    explicit FileItemWidget(bool is_remote,QString& detail, size_t size = 0, bool is_dir = false, QWidget *parent = nullptr);
    static unsigned int fileid;
    QString detail;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
signals:
    void fileItemDelete(FileItemWidget* file_id);
private:
    QIcon getIcon(const QString& path);
    
private slots:
    void onCopy();
    void onOpen();
    void onDelete();
private:
    QLabel *iconLabel;
    QLabel *textLabel;

    unsigned int file_id;
    QString file_name;
    bool is_remote;
    size_t file_size;
    bool is_dir;
    QPoint dragStartPosition;
    QFileIconProvider provider;
};

#endif //_FILEITEM_H
