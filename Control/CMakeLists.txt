#Control CMakeLists.txt
# You are in Control/CMakeLists.txt

add_library(Control STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/SettingInfo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/MessageParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/NetworkController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebrtcController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ConfigController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/EventBus.cpp

)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWEBRTC_LINUX=1 -DWEBRTC_POSIX=1")

target_include_directories(Control PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ThreadPool
)

target_link_libraries(Control Driver)
