cmake_minimum_required(VERSION 3.16)
project(DicomViewer LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(DCMTK REQUIRED)

add_executable(dicom-viewer
    src/main.cpp
    src/DicomLoader.cpp
)

target_link_libraries(dicom-viewer PRIVATE
    Qt6::Widgets
    DCMTK::DCMTK
)

