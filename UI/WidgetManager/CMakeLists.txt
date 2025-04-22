# WidgetManager  CMakeLists.txt
# You are in UI/WidgetManager/CMakeLists.txt

add_library(WidgetManager STATIC
    WidgetManager.cpp
)

target_include_directories(WidgetManager PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 链接 RemoteControlWidget 库
target_link_libraries(WidgetManager 
ConnectWidget
RemoteControlWidget 
)
