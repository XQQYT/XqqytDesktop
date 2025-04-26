#OpenGLWidget CMakeLists.txt
# You are in UI/OpenGLWidget/CMakeLists.txt

add_library(OpenGLWidget STATIC
OpenGLWidget.cpp
)

find_package(OpenGL REQUIRED)

target_include_directories(OpenGLWidget PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(OpenGLWidget PRIVATE Qt5::Widgets OpenGL::GL RemoteControlWidget)
