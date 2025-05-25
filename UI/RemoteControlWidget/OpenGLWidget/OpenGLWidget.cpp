/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "OpenGLWidget.h"
#include <QOpenGLFunctions>
#include "RemoteControlWidget.h"
#include <iostream>
#include "Render.h"
#include <fstream>

OpenGLWidget::OpenGLWidget(QWidget* parent)
    : QOpenGLWidget(parent), m_yTexture(nullptr), m_uTexture(nullptr), m_vTexture(nullptr)
{
    input_handler = new InputHandler(this);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();  // 进入OpenGL上下文
    if (m_vao) glDeleteVertexArrays(1, &m_vao);
    if (m_vbo) glDeleteBuffers(1, &m_vbo);
    if (m_ebo) glDeleteBuffers(1, &m_ebo);
    delete m_yTexture;
    delete m_uTexture;
    delete m_vTexture;
    doneCurrent();

    delete input_handler;
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

    GLfloat vertices[] = {
        // Positions      // Texture coords
        -1.0f,  1.0f,     0.0f, 0.0f,
        -1.0f, -1.0f,     0.0f, 1.0f,
         1.0f, -1.0f,     1.0f, 1.0f,
         1.0f,  1.0f,     1.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind
}

void OpenGLWidget::ensureTextureSize(QOpenGLTexture*& tex, int width, int height) {
    if (!tex || !tex->isStorageAllocated() || tex->width() != width || tex->height() != height) {
        if (tex) {
            delete tex;
        }
        tex = new QOpenGLTexture(QOpenGLTexture::Target2D);
        tex->setFormat(QOpenGLTexture::R8_UNorm);
        tex->setMinMagFilters(QOpenGLTexture::Linear, QOpenGLTexture::Linear);
        tex->setWrapMode(QOpenGLTexture::ClampToEdge);
        tex->setSize(width, height);
        tex->allocateStorage();
    }
}

void OpenGLWidget::setCurrent(RenderInterface::VideoFrame frame)
{
    float scale_x = (float)frame.width / this->width();
    float scale_y = (float)frame.height / this->height();

    input_handler->setScale(scale_x,scale_y);

    if (!frame.y_plane || !frame.u_plane || !frame.v_plane) {
        qWarning() << "Invalid frame data received!";
        return;
    }

    if (frame.width <= 0 || frame.height <= 0) {
        qWarning() << "Invalid frame dimensions:" << frame.width << "x" << frame.height;
        return;
    }

    makeCurrent();
    
    // Update Y texture
    ensureTextureSize(m_yTexture,frame.width,frame.height);
    m_yTexture->bind();
    glPixelStorei(GL_UNPACK_ROW_LENGTH, frame.stride_y);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, frame.width, frame.height, 
                   GL_RED, GL_UNSIGNED_BYTE, frame.y_plane);

    // Update U texture
    int uv_width = frame.width / 2;
    int uv_height = frame.height / 2;
    ensureTextureSize(m_uTexture,uv_width,uv_height);
    m_uTexture->bind();
    glPixelStorei(GL_UNPACK_ROW_LENGTH, frame.stride_u);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, uv_width, uv_height, 
                   GL_RED, GL_UNSIGNED_BYTE, frame.u_plane);

    // Update V texture
    ensureTextureSize(m_vTexture,uv_width,uv_height);
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
    
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    m_program.release();
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}