#Driver_Interface CMakeLists.txt
# You are in Driver_Interface/CMakeLists.txt

add_library(Driver_Interface STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Network.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/JsonFactory.cpp
)

target_include_directories(Driver_Interface PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
