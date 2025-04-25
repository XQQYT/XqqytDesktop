#include <QApplication>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <atomic>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "Render.h" 

static uint8_t buffer_count = 2;

class RemoteControlWidget;
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    void addRenderFrame(RenderInterface::VideoFrame&& render_frame);

protected:
    void initializeGL() override;

    // 绘制 OpenGL 内容
    void paintGL() override;
    // 处理窗口大小变化
    void resizeGL(int w, int h) override;
signals:
    void hasFrame();
private:
    class Framebuffer;

    GLuint textureY_;
    GLuint textureU_;
    GLuint textureV_;

    // double buffer
    Framebuffer* buffer;

    void updateTextures(const RenderInterface::VideoFrame& frame);
    void renderTextures();
};


class OpenGLWidget::Framebuffer
{
public:
    Framebuffer();
    void addFrame(RenderInterface::VideoFrame&& render_frame);
    bool getLatestFrame(RenderInterface::VideoFrame& out_frame);
private:
    std::mutex mtx;
    std::atomic<uint8_t> head{0};
    std::atomic<uint8_t> tail{0};
    RenderInterface::VideoFrame *frame_buffer;
    std::atomic<uint8_t> size{0};
    std::condition_variable has_frame;
};
