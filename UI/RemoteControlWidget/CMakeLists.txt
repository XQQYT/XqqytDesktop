#RemoteControlWidget CMakeLists.txt
# You are in UI/RemoteControlWidget/CMakeLists.txt

add_library(RemoteControlWidget STATIC
    RemoteControlWidget.cpp
    InputHandler/InputHandler.cpp
    OpenGLWidget/OpenGLWidget.cpp
    QImageWidget/QImageWidget.cpp
)

target_include_directories(RemoteControlWidget PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/RenderWidgetInterface
    ${CMAKE_CURRENT_SOURCE_DIR}/InputHandler
    ${CMAKE_CURRENT_SOURCE_DIR}/OpenGLWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/QImageWidget
)

target_link_libraries(RemoteControlWidget Qt5::Widgets Control)
