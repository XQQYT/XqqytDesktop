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
    explicit FileItemWidget(bool is_remote,QString& detail,unsigned int input_file_id = UINT_MAX, size_t file_size = ULONG_MAX, QWidget *parent = nullptr);
    static unsigned int fileid;
    QString detail;
    QString file_name;
    size_t file_size;

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
    bool is_remote;
    bool is_dir;
    QPoint dragStartPosition;
    QFileIconProvider provider;
};

#endif //_FILEITEM_H
