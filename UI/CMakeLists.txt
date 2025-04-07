# UI  CMakeLists.txt
# You are in UI/CMakeLists.txt

add_subdirectory(MainWidget)
add_subdirectory(RemoteControlWidget)

add_library(UI STATIC
    MainWidget/MainWidget.cpp
)

target_include_directories(UI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoteControlWidget  # 确保包含 RemoteControlWidget 的头文件
    ${CMAKE_CURRENT_SOURCE_DIR}/../Driver/include
)

target_link_libraries(UI Qt5::Widgets)
