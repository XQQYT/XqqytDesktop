/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef TRANSFERHUBWIDGET_H
#define TRANSFERHUBWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QScrollArea>
#include <QGridLayout>
#include "RoundedScrollArea/RoundedScrollArea.h"
#include <QList>
#include <QSet>
#include <QMap>
#include <queue>
#include <fstream>
#include "Fileitem/Fileitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class TransferHubWidget; }
QT_END_NAMESPACE

class TransferHubWidget : public QWidget
{
    Q_OBJECT

public:
    static TransferHubWidget& getInstance()
    {
        static TransferHubWidget instance;
        return instance;
    }
    ~TransferHubWidget();
    void addFile(bool is_remote,QString detail,uint16_t input_file_id = UINT16_MAX, size_t file_size = ULONG_MAX);
    void start();
    void stop();
    void reset();
public slots:
    void moveToShown();
private slots:
    void onDeleteFileItem(FileItemWidget* item);
protected:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
private:
    TransferHubWidget(QWidget *parent = nullptr);
    void prepareNextReceiveFile();
    Ui::TransferHubWidget *ui;
    QTimer* hideTimer;
    RoundedScrollArea *scrollArea;
    QGridLayout *gridLayout;

    QTimer *hoverTimer;

    int colCount = 6;
    int cur_count = 0;

    int init_x;
    int init_y;

    QList<FileItemWidget*> file_items;
    QMap<uint16_t, FileItemWidget*> id_file;
    QSet<QString> existing_etails;
    std::queue<std::pair<uint16_t,std::string>> receive_file_queue;
    uint16_t current_receive_file_id;
    std::shared_ptr<std::ofstream> current_file_stream;

};
#endif // TRANSFERHUBWIDGET_H
