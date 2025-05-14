#include "QImageWidget.h"
#include <QPainter>
#include <iostream>

QImageWidget::QImageWidget(QWidget *parent)
    : QWidget(parent)
{
    input_handler = new InputHandler(this);
    rgbBufferSize = 0;

    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

QImageWidget::~QImageWidget()
{
}

void QImageWidget::yuv420_to_rgb32(const uint8_t* yPlane, const uint8_t* uPlane, const uint8_t* vPlane,
    int stride_y, int stride_u, int stride_v,
    uint8_t* rgb, int width, int height)
{
    // 预计算常用值
    const int half_width = width / 2;
    const int half_height = height / 2;

    for (int j = 0; j < height; ++j) {
        const uint8_t* yLine = yPlane + j * stride_y;
        const uint8_t* uLine = uPlane + (j / 2) * stride_u;
        const uint8_t* vLine = vPlane + (j / 2) * stride_v;
        uint8_t* rgbLine = rgb + j * width * 4;

        for (int i = 0; i < width; ++i) {
            int y = yLine[i];
            int u = uLine[i / 2];
            int v = vLine[i / 2];

            // 使用整数运算代替浮点运算
            int c = y - 16;
            int d = u - 128;
            int e = v - 128;

            int r = (298 * c + 409 * e + 128) >> 8;
            int g = (298 * c - 100 * d - 208 * e + 128) >> 8;
            int b = (298 * c + 516 * d + 128) >> 8;

            // 使用位运算代替数组索引
            rgbLine[i*4 + 0] = std::clamp(b, 0, 255);
            rgbLine[i*4 + 1] = std::clamp(g, 0, 255);
            rgbLine[i*4 + 2] = std::clamp(r, 0, 255);
            rgbLine[i*4 + 3] = 255;
        }
    }
}

void QImageWidget::setCurrent(RenderInterface::VideoFrame frame)
{
    if (!render_frame_done.load(std::memory_order_acquire))
        return;

    int width = frame.width;
    int height = frame.height;
    float scale_x = (float)width / this->width();
    float scale_y = (float)height / this->height();

    input_handler->setScale(scale_x,scale_y);
    
    size_t requiredSize = width * height * 4;
    if (rgbBufferSize < requiredSize) {
        rgbBuffer.reset(new uint8_t[requiredSize]);
        rgbBufferSize = requiredSize;
    }

    yuv420_to_rgb32(frame.y_plane, frame.u_plane, frame.v_plane,
                   frame.stride_y, frame.stride_u, frame.stride_v,
                   rgbBuffer.get(), width, height);

    QImage image(rgbBuffer.get(), width, height, QImage::Format_RGB32);
    
    {
        std::lock_guard<std::mutex> lock(image_mutex);
        currentImage = image.copy();
    }

    render_frame_done.store(false, std::memory_order_release);
    QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
}


void QImageWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QImage image;
    {
        std::lock_guard<std::mutex> lock(image_mutex);
        image = currentImage;
    }

    if (!image.isNull()) {
        QPainter painter(this);
        painter.drawImage(rect(), image);
    }

    render_frame_done.store(true, std::memory_order_release);
}
