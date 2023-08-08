cmake_minimum_required(VERSION 3.24.1)
project(opengl_lib)
# 开启 AddressSanitizer
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")
add_library(opengl_lib STATIC src/glad.c ${SOURCES})

if(LINUX)
    find_package(glfw3 REQUIRED)
    target_link_libraries(opengl_lib glfw)
endif(LINUX)

if(WIN32)
    target_link_libraries(opengl_lib PRIVATE ${PROJECT_SOURCE_DIR}/lib/windows-x86_64/glfw3.lib)
    target_link_libraries(opengl_lib PRIVATE ${PROJECT_SOURCE_DIR}/lib/windows-x86_64/freetype.lib)
endif(WIN32)

if(APPLE)
    target_link_libraries(opengl_lib PRIVATE ${PROJECT_SOURCE_DIR}/lib/darwin-arm64/libglfw.3.dylib)
    target_link_libraries(opengl_lib PRIVATE ${PROJECT_SOURCE_DIR}/lib/darwin-arm64/libglfw3.a)
endif(APPLE)