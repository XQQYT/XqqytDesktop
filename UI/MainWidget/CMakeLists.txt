# MainWidget  CMakeLists.txt
# You are in UI/MainWidget/CMakeLists.txt

add_library(MainWidget STATIC
    MainWidget.cpp
)

# 添加 RemoteControlWidget 的头文件目录
target_include_directories(MainWidget PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../RemoteControlWidget 
)

# 链接 RemoteControlWidget 库
target_link_libraries(MainWidget RemoteControlWidget Qt5::Widgets)
