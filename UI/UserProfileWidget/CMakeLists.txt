# UserProfileWidget  CMakeLists.txt
# You are in UI/UserProfileWidget/CMakeLists.txt

add_library(UserProfileWidget STATIC
    UserProfileWidget.cpp
)

# 添加 UserProfileWidget 的头文件目录
target_include_directories(UserProfileWidget PUBLIC
    ${PROJECT_SOURCE_DIR}/UI/UserProfileWidget
)

target_link_libraries(UserProfileWidget 
Qt5::Widgets 
Control
utils
)
