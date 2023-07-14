cmake_minimum_required(VERSION 3.24.1)
project(main)
# 开启 AddressSanitizer
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main src/glad.c src/glfw.cpp src/shader.cpp src/main.cpp)

if(LINUX)
    find_package(glfw3 REQUIRED)
    target_link_libraries(main glfw)
endif(LINUX)

if(WIN32)
    target_link_libraries(main PRIVATE ${PROJECT_SOURCE_DIR}/lib/windows-x86_64/glfw3.lib)
    target_link_libraries(main PRIVATE ${PROJECT_SOURCE_DIR}/lib/windows-x86_64/freetype.lib)
endif(WIN32)