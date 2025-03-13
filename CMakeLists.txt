cmake_minimum_required(VERSION 3.5)

project(XqqytDesktop)

set(CMAKE_PREFIX_PATH "/opt/Qt5.14.2/5.14.2/gcc_64")

# 查找Qt5库，指定需要的Widgets模块
find_package(Qt5 REQUIRED COMPONENTS Widgets)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)

# 添加源文件
set(SOURCES
    main.cpp
)

# 添加头文件
set(HEADERS
    
)

# 如果有UI文件（如 .ui 文件），可以这样添加：
# set(UI_FILES
#     mainwindow.ui
# )

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# 链接Qt5的Widgets库
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
