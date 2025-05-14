/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef QIMAGEWIDGET_H
#define QIMAGEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <atomic>
#include "InputHandler/InputHandler.h"
#include "RenderWidgetInterface/RenderWidgetInterface.h"

class QImageWidget : public QWidget, public RenderWidgetInterface
{
    Q_OBJECT

public:
    QImageWidget(QWidget *parent = nullptr);
    ~QImageWidget();
    void setCurrent(RenderInterface::VideoFrame frame) override;
    void mouseMoveEvent(QMouseEvent* event) override
    {
        std::cout<<"move"<<std::endl;
        input_handler->handleMouseMoveEvent(event);
    }
    void mousePressEvent(QMouseEvent* event) override
    {
        input_handler->handleMousePressEvent(event);
    }
    void mouseReleaseEvent(QMouseEvent* event) override
    {
        input_handler->handleMouseReleaseEvent(event);
    }
    void wheelEvent(QWheelEvent* event) override
    {
        input_handler->handleWheelEvent(event);
    }

    void keyPressEvent(QKeyEvent* event) override
    {
        input_handler->handleKeyPressEvent(event);
    }
    void keyReleaseEvent(QKeyEvent* event) override
    {
        input_handler->handleKeyReleaseEvent(event);
    }

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    void yuv420_to_rgb32(const uint8_t* yPlane, const uint8_t* uPlane, const uint8_t* vPlane,
        int stride_y, int stride_u, int stride_v,
        uint8_t* rgb, int width, int height);

    std::mutex image_mutex;
    std::atomic<bool> render_frame_done = true;

    std::unique_ptr<uint8_t[]> rgbBuffer;
    size_t rgbBufferSize = 0;

    QImage currentImage;
    InputHandler *input_handler;
};
#endif // QIMAGEWIDGET_H
