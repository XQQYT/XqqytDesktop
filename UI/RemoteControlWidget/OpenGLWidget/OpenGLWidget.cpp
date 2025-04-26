#include "OpenGLWidget.h"
#include <QOpenGLFunctions>
#include "RemoteControlWidget.h"
#include <iostream>
#include "Render.h"
#include <fstream>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent), m_yTexture(nullptr), m_uTexture(nullptr), m_vTexture(nullptr)
{
    hold_timer = new QTimer(this);
    connect(hold_timer, &QTimer::timeout, this, &OpenGLWidget::sendHoldPackets);
    hold_timer->start(50);
}

OpenGLWidget::~OpenGLWidget()
{
    delete m_yTexture;
    delete m_uTexture;
    delete m_vTexture;
    hold_timer->stop();
    delete hold_timer;
}

void OpenGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Initialize shader program
    m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program.link();

    // Create textures but don't allocate storage yet - we'll do that when we get frames
    m_yTexture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_uTexture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    m_vTexture = new QOpenGLTexture(QOpenGLTexture::Target2D);

    // Configure textures
    for (auto tex : {m_yTexture, m_uTexture, m_vTexture}) {
        tex->setFormat(QOpenGLTexture::R8_UNorm);
        tex->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
        tex->setWrapMode(QOpenGLTexture::ClampToEdge);
    }
}

void OpenGLWidget::setCurrent(RenderInterface::VideoFrame frame)
{
    scale_x = (float)frame.width / this->width();
    scale_y = (float)frame.height / this->height();
    
    makeCurrent();
    
    // Update Y texture
    if (!m_yTexture->isStorageAllocated() || 
        m_yTexture->width() != frame.width || 
        m_yTexture->height() != frame.height) {
        m_yTexture->setSize(frame.width, frame.height);
        m_yTexture->allocateStorage();
    }
    m_yTexture->bind();
    glPixelStorei(GL_UNPACK_ROW_LENGTH, frame.stride_y);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, frame.width, frame.height, 
                   GL_RED, GL_UNSIGNED_BYTE, frame.y_plane);

    // Update U texture
    int uv_width = frame.width / 2;
    int uv_height = frame.height / 2;
    if (!m_uTexture->isStorageAllocated() || 
        m_uTexture->width() != uv_width || 
        m_uTexture->height() != uv_height) {
        m_uTexture->setSize(uv_width, uv_height);
        m_uTexture->allocateStorage();
    }
    m_uTexture->bind();
    glPixelStorei(GL_UNPACK_ROW_LENGTH, frame.stride_u);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, uv_width, uv_height, 
                   GL_RED, GL_UNSIGNED_BYTE, frame.u_plane);

    // Update V texture
    if (!m_vTexture->isStorageAllocated() || 
        m_vTexture->width() != uv_width || 
        m_vTexture->height() != uv_height) {
        m_vTexture->setSize(uv_width, uv_height);
        m_vTexture->allocateStorage();
    }
    m_vTexture->bind();
    glPixelStorei(GL_UNPACK_ROW_LENGTH, frame.stride_v);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, uv_width, uv_height, 
                   GL_RED, GL_UNSIGNED_BYTE, frame.v_plane);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    doneCurrent();
    update();
}

void OpenGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (!m_yTexture || !m_uTexture || !m_vTexture || 
        !m_yTexture->isStorageAllocated()) {
        return;
    }

    m_program.bind();

    // Bind textures
    m_yTexture->bind(0);
    m_uTexture->bind(1);
    m_vTexture->bind(2);
    
    m_program.setUniformValue("yTexture", 0);
    m_program.setUniformValue("uTexture", 1);
    m_program.setUniformValue("vTexture", 2);

    GLfloat vertices[] = {
        // Positions      // Texture coords (Y flipped)
        -1.0f,  1.0f,     0.0f, 0.0f,
        -1.0f, -1.0f,     0.0f, 1.0f,
         1.0f, -1.0f,     1.0f, 1.0f,
         1.0f,  1.0f,     1.0f, 0.0f
    };
    
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    
    // Texture coordinate attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    m_program.release();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void OpenGLWidget::convertPos(MouseEventPacket& packet)
{
    packet.x = packet.x * scale_x;
    packet.y = packet.y * scale_y;
    qDebug() << "Remote screen coordinates: (" << packet.x << ", " << packet.y << ")";
}

MouseButton OpenGLWidget::toMouseButton(Qt::MouseButton qtButton)
{
    switch (qtButton)
    {
    case Qt::LeftButton:
        return MouseButton::LeftButton;
    case Qt::RightButton:
        return MouseButton::RightButton;
    case Qt::MiddleButton:
        return MouseButton::MiddleButton;
    default:
        return MouseButton::NoButton;
    }
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (!event | left_button_pressed |right_button_pressed) return;

    QPoint pos = event->pos();

    MouseEventPacket packet;
    packet.type = MouseEventType::Move;
    packet.button = MouseButton::NoButton;
    packet.x = pos.x();
    packet.y = pos.y();
    packet.wheelDelta = 0;
    convertPos(packet);
    EventBus::getInstance().publish("/mouse_event/has_event",packet);
}

void OpenGLWidget::mousePressEvent(QMouseEvent* event)
{
    if (!event) return;

    if (event->button() == Qt::LeftButton)
        left_button_pressed = true;
    if (event->button() == Qt::RightButton)
        right_button_pressed = true;

    QPoint pos = event->pos();

    MouseEventPacket packet;
    packet.type = MouseEventType::Press;
    packet.button = toMouseButton(event->button());
    packet.x = pos.x();
    packet.y = pos.y();
    packet.wheelDelta = 0;
    convertPos(packet);
    EventBus::getInstance().publish("/mouse_event/has_event",packet);
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (!event) return;

    if (event->button() == Qt::LeftButton)
        left_button_pressed = false;
    if (event->button() == Qt::RightButton)
        right_button_pressed = false;

    QPoint pos = event->pos();

    MouseEventPacket packet;
    packet.type = MouseEventType::Release;
    packet.button = toMouseButton(event->button()); // 哪个键释放
    packet.x = pos.x();
    packet.y = pos.y();
    packet.wheelDelta = 0; // 无滚轮
    convertPos(packet);
    EventBus::getInstance().publish("/mouse_event/has_event",packet);
}

void OpenGLWidget::wheelEvent(QWheelEvent* event)
{
    if (!event) return;

    QPoint pos = event->position().toPoint(); // Qt6用position()，Qt5用pos()

    MouseEventPacket packet;
    packet.type = MouseEventType::Wheel;
    packet.button = MouseButton::NoButton; // 滚轮事件没有按钮
    packet.x = pos.x();
    packet.y = pos.y();
    packet.wheelDelta = event->angleDelta().y(); // y方向的滚动，单位通常是120或-120
    convertPos(packet);
    EventBus::getInstance().publish("/mouse_event/has_event",packet);
}

void OpenGLWidget::sendHoldPackets()
{
    QPoint pos = mapFromGlobal(QCursor::pos()); // 获取当前鼠标位置（相对于窗口）

    if (rect().contains(pos)) { // 确保鼠标还在窗口内
        if (left_button_pressed || right_button_pressed) {
            MouseEventPacket packet;
            packet.type = MouseEventType::Hold;
            packet.button = left_button_pressed ? MouseButton::LeftButton :
                           right_button_pressed ? MouseButton::RightButton :
                           MouseButton::NoButton;
            packet.x = pos.x();
            packet.y = pos.y();
            packet.wheelDelta = 0;
            convertPos(packet);
            EventBus::getInstance().publish("/mouse_event/has_event", packet);
        }
    }
}

void OpenGLWidget::keyPressEvent(QKeyEvent* event)
{
    std::cout<<"keyPressEvent"<<std::endl;
    KeyEventPacket packet;
    packet.key = event->key();
    packet.modifiers = event->modifiers();
    packet.is_pressed = true;
    EventBus::getInstance().publish("/keyboard_event/has_event",packet);
}

void OpenGLWidget::keyReleaseEvent(QKeyEvent* event)
{
    std::cout<<"keyReleaseEvent"<<std::endl;
    KeyEventPacket packet;
    packet.key = event->key();
    packet.modifiers = event->modifiers();
    packet.is_pressed = false;
    EventBus::getInstance().publish("/keyboard_event/has_event",packet);
}