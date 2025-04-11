# MainWidget  CMakeLists.txt
# You are in UI/MainWidget/CMakeLists.txt

add_library(MainWidget STATIC
    MainWidget.cpp
)

find_package(nlohmann_json REQUIRED)

# 添加 RemoteControlWidget 的头文件目录
target_include_directories(MainWidget PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/UI/RemoteControlWidget 
    ${CMAKE_CURRENT_SOURCE_DIR}/Control/include
    ${CMAKE_SOURCE_DIR}/UI/Dialog/Notify
)

# 链接 RemoteControlWidget 库
target_link_libraries(MainWidget 
Dialog
RemoteControlWidget 
Qt5::Widgets 
Control
nlohmann_json::nlohmann_json
)
