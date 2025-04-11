#Control CMakeLists.txt
# You are in Control/CMakeLists.txt

add_library(Control STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/MessageParser.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/NetworkController.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/EventBus.cpp
)

target_include_directories(Control PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/Driver/include
)

target_link_libraries(Control Driver)
