#Driver CMakeLists.txt
# You are in Driver/CMakeLists.txt

add_library(Driver STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/websocket.cpp
)

target_include_directories(Driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Driver Driver_Interface boost_system)
