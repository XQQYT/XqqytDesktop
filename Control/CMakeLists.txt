#Control CMakeLists.txt
# You are in Control/CMakeLists.txt

add_library(Control STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/SettingInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/SignalMessageParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/NetworkController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebrtcController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ConfigController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/EventBus.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/UserServerMsgParser/StrategyInterface.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/UserServerMsgParser/BinaryStrategyUser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/UserServerMsgParser/JsonStrategyUser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/UserServerMsgParser/UserServerParser.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWEBRTC_LINUX=1 -DWEBRTC_POSIX=1")

target_include_directories(Control PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ThreadPool
    ${CMAKE_CURRENT_SOURCE_DIR}/include/UserServerMsgParser
)

target_link_libraries(Control Driver)
