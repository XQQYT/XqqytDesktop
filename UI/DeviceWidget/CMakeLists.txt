# DeviceWidget  CMakeLists.txt
# You are in UI/DeviceWidget/CMakeLists.txt

add_subdirectory(DeviceItem)

add_library(DeviceWidget STATIC
DeviceWidget.cpp
)

# 添加 DeviceWidget 的头文件目录
target_include_directories(DeviceWidget PUBLIC
    ${PROJECT_SOURCE_DIR}/UI/DeviceWidget
)

# 链接 DeviceWidget 库
target_link_libraries(DeviceWidget 
Qt5::Widgets 
Dialog
WidgetManager
DeviceItem
utils
Control
)
