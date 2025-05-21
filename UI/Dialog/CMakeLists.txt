# UI/Dialog/CMakeLists.txt
add_library(Dialog STATIC
    Notify/BubbleMessage.cpp
    Dialog/ConfirmBeConnectDialog/ConfirmBeConnectDialog.cpp
    Dialog/ConfirmDialog/ConfirmDialog.cpp
    Dialog/InfoDialog/InfoDialog.cpp
    Dialog/LoginDialog/LoginDialog.cpp
    Dialog/LoadingDialog/LoadingDialog.cpp
    Dialog/RegisterDialog/RegisterDialog.cpp
    Dialog/KeyAuthenticationDialog/KeyAuthenticationDialog.cpp
    Dialog/GeneralLineEditDialog/GeneralLineEditDialog.cpp
)

target_include_directories(Dialog PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Notify
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/ConfirmBeConnectDialog
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/ConfirmDialog
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/LoadingDialog
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/InfoDialog
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/LoginDialog
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/RegisterDialog
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/KeyAuthenticationDialog
    ${CMAKE_CURRENT_SOURCE_DIR}/Dialog/GeneralLineEditDialog
)

target_link_libraries(Dialog
    Qt5::Core
    Qt5::Widgets
    Control
    utils
)