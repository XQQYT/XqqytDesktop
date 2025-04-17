# Driver_Interface/CMakeLists.txt

add_library(Driver_Interface INTERFACE)

target_include_directories(Driver_Interface INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
