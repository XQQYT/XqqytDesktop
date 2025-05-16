#Driver CMakeLists.txt
# You are in Driver/CMakeLists.txt

add_library(Driver STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/NetworkDriver/WebSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/NetworkDriver/TcpDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/MsgBuilder/UserServerMsg.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/NlohmannJson.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/OpensslDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ConfigDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/WebRTC.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/DataChannelObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/PeerConnectionObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/SdpObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/DesktopCaptureSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/VideoRender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/AudioDriver/Capturer/PulseAudioCapture.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/AudioDriver/Player/PulseAudioPlayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/KeyboardMouseDriver/X11KeyboardMouseDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ClipboardDriver/X11ClipboardDriver.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWEBRTC_LINUX=1 -DWEBRTC_POSIX=1 -frtti -DNDEBUG -DWEBRTC_USE_X11 -DWEBRTC_USE_PIPEWIRE")
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0 gobject-2.0 gio-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})
add_definitions(${GLIB_CFLAGS_OTHER} )

find_package(X11 REQUIRED)
find_package(ZLIB REQUIRED)

target_include_directories(Driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/WebRTC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/NetworkDriver
    ${CMAKE_CURRENT_SOURCE_DIR}/include/MsgBuilder
    ${CMAKE_CURRENT_SOURCE_DIR}/include/AudioDriver/Capturer
    ${CMAKE_CURRENT_SOURCE_DIR}/include/AudioDriver/Player
    ${CMAKE_SOURCE_DIR}/third_party/webrtc/include
    ${CMAKE_SOURCE_DIR}/third_party/webrtc/include/third_party/libyuv/include

)

target_link_libraries(Driver 
    ${CMAKE_SOURCE_DIR}/third_party/webrtc/lib/libwebrtc.a
    Driver_Interface 
    boost_system
    ${X11_LIBRARIES}
    Xcomposite
    Xfixes
    Xrandr
    Xrender
    Xdamage
    Xtst
    gbm
    drm
    pulse-simple
    pulse
    ${GLIB_LIBRARIES}
    ssl 
    crypto
    ZLIB::ZLIB
)
