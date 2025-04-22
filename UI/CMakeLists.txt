# UI  CMakeLists.txt
# You are in UI/CMakeLists.txt

add_subdirectory(Dialog)
add_subdirectory(WidgetManager)
add_subdirectory(MainWidget)
add_subdirectory(ConnectWidget)
add_subdirectory(RemoteControlWidget)


add_library(UI STATIC
    ConnectWidget/ConnectWidget.cpp
)

target_include_directories(UI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ConnectWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/RemoteControlWidget
)

target_link_libraries(UI 
    Qt5::Widgets
    ConnectWidget)
