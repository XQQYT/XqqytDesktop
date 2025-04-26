#Driver CMakeLists.txt
# You are in Driver/CMakeLists.txt

add_library(Driver STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebSocket.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/NlohmannJson.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/WebRTC.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/DataChannelObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/PeerConnectionObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/SdpObserver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/DesktopCaptureSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/WebRTC/VideoRender.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWEBRTC_LINUX=1 -DWEBRTC_POSIX=1 -frtti -DNDEBUG -DWEBRTC_USE_X11 -DWEBRTC_USE_PIPEWIRE")
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0 gobject-2.0 gio-2.0)

include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})
add_definitions(${GLIB_CFLAGS_OTHER} )

find_package(X11 REQUIRED)

target_include_directories(Driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/WebRTC
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
    ${GLIB_LIBRARIES}
)
