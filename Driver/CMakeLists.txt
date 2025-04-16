#Driver CMakeLists.txt
# You are in Driver/CMakeLists.txt

add_library(Driver STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/NlohmannJson.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/WebRTC.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/DataChannelObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/IceOberver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/PeerConnectionObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/SdpObserver.cpp

)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWEBRTC_LINUX=1 -DWEBRTC_POSIX=1")

target_include_directories(Driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/WebRTC
    ${CMAKE_SOURCE_DIR}/third_party/webrtc/include
)

target_link_libraries(Driver 
${CMAKE_SOURCE_DIR}/third_party/webrtc/lib/libwebrtc.a
Driver_Interface 
boost_system
X11
)
