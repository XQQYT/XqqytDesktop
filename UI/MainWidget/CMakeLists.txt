# MainWidget  CMakeLists.txt
# You are in UI/MainWidget/CMakeLists.txt

add_library(MainWidget STATIC
    MainWidget.cpp
)

# 添加 RemoteControlWidget 的头文件目录
target_include_directories(MainWidget PUBLIC
    ${PROJECT_SOURCE_DIR}/UI/MainWidget
)

# 链接 RemoteControlWidget 库
target_link_libraries(MainWidget 
WidgetManager
Dialog
Qt5::Widgets 
Control
)
