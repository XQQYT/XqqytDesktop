#utils CMakeLists.txt
# You are in UI/utils/CMakeLists.txt

add_library(utils STATIC
    utils.cpp
)

target_include_directories(utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(utils Qt5::Widgets)
