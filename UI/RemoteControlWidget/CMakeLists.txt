#RemoteControlWidget CMakeLists.txt
# You are in UI/RemoteControlWidget/CMakeLists.txt

add_subdirectory(OpenGLWidget)

add_library(RemoteControlWidget STATIC
    RemoteControlWidget.cpp
)

target_include_directories(RemoteControlWidget PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(RemoteControlWidget Qt5::Widgets Control OpenGLWidget)
