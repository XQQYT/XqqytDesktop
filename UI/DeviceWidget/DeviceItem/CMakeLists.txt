# DeviceItem  CMakeLists.txt
# You are in UI/DeviceItem/CMakeLists.txt

add_library(DeviceItem STATIC
DeviceItem.cpp
)

# 添加 DeviceItem 的头文件目录
target_include_directories(DeviceItem PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接 DeviceItem 库
target_link_libraries(DeviceItem 
Qt5::Widgets 
utils
)
