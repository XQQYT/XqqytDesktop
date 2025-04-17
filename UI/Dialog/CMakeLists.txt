# UI/Dialog/CMakeLists.txt
add_library(Dialog STATIC
    Notify/BubbleMessage.cpp
    Dialog/ConfirmBeConnectDialog/ConfirmBeConnectDialog.cpp
)

target_include_directories(Dialog PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Notify
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/ConfirmBeConnectDialog
)

target_link_libraries(Dialog
    Qt5::Core
    Qt5::Widgets
)