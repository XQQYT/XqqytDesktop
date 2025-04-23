#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget(parent) 
{
    
}

OpenGLWidget::~OpenGLWidget()
{

}

void OpenGLWidget::initializeGL()
{
    // 初始化 OpenGL 函数
    initializeOpenGLFunctions();
    
    // 设置清屏颜色为黑色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

void OpenGLWidget::paintGL()
{
    // 清空屏幕
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.0f, 0.0f); // 设置颜色为红色
    glBegin(GL_TRIANGLES);        // 开始绘制三角形
    glVertex2f(-0.5f, -0.5f);    // 第一个顶点
    glVertex2f(0.5f, -0.5f);     // 第二个顶点
    glVertex2f(0.0f, 0.5f);      // 第三个顶点
    glEnd();                      // 结束绘制
}

void OpenGLWidget::resizeGL(int w, int h){
    // 设置视口大小为窗口的宽高
    glViewport(0, 0, w, h);

    // 设置投影矩阵为正交投影
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 正交投影
    glMatrixMode(GL_MODELVIEW);
}