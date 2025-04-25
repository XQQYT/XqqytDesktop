#include "OpenGLWidget.h"
#include <QOpenGLFunctions>
#include "RemoteControlWidget.h"
#include <iostream>
#include "Render.h"

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , textureY_(0)
    , textureU_(0)
    , textureV_(0)
{
    buffer = new Framebuffer();
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();
    glDeleteTextures(1, &textureY_);
    glDeleteTextures(1, &textureU_);
    glDeleteTextures(1, &textureV_);
    delete[] buffer;
}

void OpenGLWidget::initializeGL()
{
    std::cout<<"initializeGL thread id "<<std::this_thread::get_id()<<std::endl;
    initializeOpenGLFunctions();

        // 初始化纹理
    glGenTextures(1, &textureY_);
    glGenTextures(1, &textureU_);
    glGenTextures(1, &textureV_);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    std::cout<<"initializeGL done"<<std::endl;

}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}


void OpenGLWidget::paintGL() {
    RenderInterface::VideoFrame frame;
    if (!buffer->getLatestFrame(frame) || frame.y_plane == nullptr) {
        // 没有新帧时渲染黑色背景
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        return;
    }

    // 更新纹理
    updateTextures(frame);
    
    // 执行渲染
    renderTextures();
}

void OpenGLWidget::updateTextures(const RenderInterface::VideoFrame& frame) {
    // 更新 Y 分量
    glBindTexture(GL_TEXTURE_2D, textureY_);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 
                   frame.width, frame.height, 
                   GL_RED, GL_UNSIGNED_BYTE, frame.y_plane);

    // 更新 U 分量
    glBindTexture(GL_TEXTURE_2D, textureU_);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 
                   frame.width/2, frame.height/2, 
                   GL_RED, GL_UNSIGNED_BYTE, frame.u_plane);

    // 更新 V 分量
    glBindTexture(GL_TEXTURE_2D, textureV_);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 
                   frame.width/2, frame.height/2, 
                   GL_RED, GL_UNSIGNED_BYTE, frame.v_plane);
}

void OpenGLWidget::renderTextures() {
    // 这里添加您的渲染逻辑，使用已更新的纹理
    // ...
}

void OpenGLWidget::addRenderFrame(RenderInterface::VideoFrame&& frame)
{
    buffer->addFrame(std::move(frame));
}


OpenGLWidget::Framebuffer::Framebuffer()
{
    frame_buffer = new RenderInterface::VideoFrame[buffer_count];
}


bool OpenGLWidget::Framebuffer::getLatestFrame(RenderInterface::VideoFrame& out_frame) {
    std::lock_guard<std::mutex> lock(mtx);
    if (size.load() == 0) {
        return false;
    }
    out_frame = frame_buffer[(head.load() + size.load() - 1) % buffer_count];
    return true;
}

void OpenGLWidget::Framebuffer::addFrame(RenderInterface::VideoFrame&& render_frame)
{
   if (size.load() == buffer_count)
   {
       return; // 队列已满，忽略新的帧
   }
   uint8_t frame_index = tail.load();
   frame_buffer[frame_index] = std::move(render_frame);
   tail.store((frame_index + 1) % buffer_count);
   size++;
   has_frame.notify_one();
}