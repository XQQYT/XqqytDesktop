cmake_minimum_required(VERSION 3.20)

project(XqqytDesktop VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt路径
set(CMAKE_PREFIX_PATH "/opt/Qt5.14.2/5.14.2/gcc_64")

# Find the Qt5 Widgets module
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

# Enable automatic handling of moc, ui, and rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


# 添加包含目录
include_directories(UI/MainWidget)

# 添加子项目
add_subdirectory(UI)

# Define the executable target
add_executable(${PROJECT_NAME}
    main.cpp
)

# Link against Qt5 Widgets
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets UI RemoteControlWidget)
