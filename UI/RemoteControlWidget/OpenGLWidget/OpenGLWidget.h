#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLExtraFunctions>
#include <QMouseEvent>
#include <QTimer>
#include "Render.h" 
#include "EventBus.h"
#include "MouseKeyboardType.h"

class RemoteControlWidget;
class OpenGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
    void setCurrent(RenderInterface::VideoFrame frame);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void convertPos(MouseEventPacket& packet);
    MouseButton toMouseButton(Qt::MouseButton qtButton);
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void sendHoldPackets();
private:
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

            // YUV to RGB conversion
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
   
    float scale_x;
    float scale_y;

    QTimer* hold_timer = nullptr;
    bool left_button_pressed = false;
    bool right_button_pressed = false;
};
