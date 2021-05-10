cmake_minimum_required(VERSION 3.19)
project(jsonToDepthImage)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(jsonToDepthImage main.cpp)
target_link_libraries(jsonToDepthImage ${OpenCV_LIBS} nlohmann_json::nlohmann_json)