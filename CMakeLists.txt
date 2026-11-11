cmake_minimum_required(VERSION 3.11)

project(hello_oop)

find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)

include_directories(include tasks)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main main.cpp tasks/detector.cpp tasks/plotter.cpp)

target_link_libraries(main ${OpenCV_LIBS} fmt::fmt)