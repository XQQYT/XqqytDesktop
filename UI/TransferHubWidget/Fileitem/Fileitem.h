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
    explicit FileItemWidget(bool is_remote,QString& detail,uint16_t input_file_id = UINT16_MAX, size_t file_size = ULONG_MAX, QWidget *parent = nullptr);
    static uint16_t fileid;
    QString detail;
    QString file_name;
    size_t file_size;
    uint16_t getID(){return file_id;}
    void setProgress(int percent);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
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

    uint16_t file_id;
    bool is_remote;
    QPoint dragStartPosition;
    QFileIconProvider provider;

    int m_progress = 0;
    QColor m_progressColor = QColor(0, 150, 255); // 进度条颜色

};

#endif //_FILEITEM_H
