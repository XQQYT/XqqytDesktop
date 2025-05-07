# ItemWidget  CMakeLists.txt
# You are in UI/SettingsWidget/ItemWidget/CMakeLists.txt

add_library(ItemWidget STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneralWidget/GeneralWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DisplayWidget/DisplayWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkWidget/NetworkWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AboutWidget/AboutWidget.cpp
)

# 添加 ItemWidget 的头文件目录
target_include_directories(ItemWidget PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/GeneralWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/DisplayWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/NetworkWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/AboutWidget
)

# 链接 ItemWidget 库
target_link_libraries(ItemWidget 
Qt5::Widgets
utils
)
