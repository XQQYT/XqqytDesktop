# ConnectWidget  CMakeLists.txt
# You are in UI/ConnectWidget/CMakeLists.txt

add_library(ConnectWidget STATIC
    ConnectWidget.cpp
)

find_package(nlohmann_json REQUIRED)

# 添加 RemoteControlWidget 的头文件目录
target_include_directories(ConnectWidget PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接 RemoteControlWidget 库
target_link_libraries(ConnectWidget 
Dialog
RemoteControlWidget 
Qt5::Widgets 
Control
nlohmann_json::nlohmann_json
)
