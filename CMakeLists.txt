cmake_minimum_required(VERSION 3.24.1)
project(main)

set(CMAKE_CXX_STANDARD 17)
include_directories(${PROJECT_SOURCE_DIR}/include)


add_executable(main src/glad.c src/glfw.cpp src/input.cpp src/main.cpp)

find_package(glfw3 REQUIRED)

target_link_libraries(main glfw)