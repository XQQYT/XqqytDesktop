# UI  CMakeLists.txt
# You are in UI/CMakeLists.txt

add_subdirectory(utils)
add_subdirectory(Dialog)
add_subdirectory(WidgetManager)
add_subdirectory(MainWidget)
add_subdirectory(TransferHubWidget)
add_subdirectory(UserProfileWidget)
add_subdirectory(ConnectWidget)
add_subdirectory(RemoteControlWidget)
add_subdirectory(DeviceWidget)
add_subdirectory(SettingsWidget)

add_library(UI STATIC
    MainWidget/MainWidget.cpp
)

target_include_directories(UI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWidget
)

target_link_libraries(UI 
    Qt5::Widgets
    MainWidget)
