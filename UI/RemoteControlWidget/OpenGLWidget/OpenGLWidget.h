/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QTimer>
#include "InputHandler/InputHandler.h"
#include "RenderWidgetInterface/RenderWidgetInterface.h"

class RemoteControlWidget;
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions , public RenderWidgetInterface
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    void setCurrent(RenderInterface::VideoFrame frame) override;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void mouseMoveEvent(QMouseEvent* event) override
    {
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

private:

    void ensureTextureSize(QOpenGLTexture*& tex, int width, int height);

    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec4 vertexPosition;
        layout(location = 1) in vec2 texCoord;
        out vec2 fragTexCoord;
        void main()
        {
            gl_Position = vertexPosition;
            fragTexCoord = texCoord;
        })";

    const char* fragmentShaderSource = R"(
            #version 330 core
            in vec2 fragTexCoord;
            out vec4 fragColor;

            uniform sampler2D yTexture;
            uniform sampler2D uTexture;
            uniform sampler2D vTexture;

            void main()
            {
                float y = texture(yTexture, fragTexCoord).r;
                float u = texture(uTexture, fragTexCoord).r - 0.5;
                float v = texture(vTexture, fragTexCoord).r - 0.5;

                // Y range correction (if your YUV is limited range)
                y = (y - 16.0/255.0) * (255.0/(235.0-16.0));

                float r = y + 1.402 * v;
                float g = y - 0.344136 * u - 0.714136 * v;
                float b = y + 1.772 * u;

                fragColor = vec4(r, g, b, 1.0);
            })";

    QOpenGLShaderProgram m_program;
    QOpenGLTexture* m_yTexture = nullptr;
    QOpenGLTexture* m_uTexture = nullptr;
    QOpenGLTexture* m_vTexture = nullptr;

    const uint8_t* m_yData = nullptr;
    const uint8_t* m_uData = nullptr;
    const uint8_t* m_vData = nullptr;
    int m_width = 0;
    int m_height = 0;

    // OpenGL buffer handles
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;

    InputHandler *input_handler;
};
