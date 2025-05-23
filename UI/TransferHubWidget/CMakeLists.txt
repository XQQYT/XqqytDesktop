# TransferHubWidget  CMakeLists.txt
# You are in UI/TransferHubWidget/CMakeLists.txt

add_library(TransferHubWidget STATIC
TransferHubWidget.cpp
RoundedScrollArea/RoundedScrollArea.cpp
Fileitem/Fileitem.cpp
)

target_include_directories(TransferHubWidget PUBLIC
    ${PROJECT_SOURCE_DIR}/UI/TransferHubWidget
    ${PROJECT_SOURCE_DIR}/UI/TransferHubWidget/RoundedScrollArea
    ${PROJECT_SOURCE_DIR}/UI/TransferHubWidget/Fileitem
)

target_link_libraries(TransferHubWidget 
Qt5::Widgets
)
