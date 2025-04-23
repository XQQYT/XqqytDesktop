#include <QApplication>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
protected:
    void initializeGL() override;

// 绘制 OpenGL 内容
void paintGL() override;

// 处理窗口大小变化
void resizeGL(int w, int h) override;
};


