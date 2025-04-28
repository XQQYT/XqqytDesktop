# SettingsWidget  CMakeLists.txt
# You are in UI/SettingsWidget/CMakeLists.txt

add_subdirectory(ItemWidget)

add_library(SettingsWidget STATIC
SettingsWidget.cpp
)

# 添加 SettingsWidget 的头文件目录
target_include_directories(SettingsWidget PUBLIC
    ${PROJECT_SOURCE_DIR}/UI/SettingsWidget
)

# 链接 SettingsWidget 库
target_link_libraries(SettingsWidget 
Qt5::Widgets
ItemWidget
)
