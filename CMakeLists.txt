cmake_minimum_required(VERSION 3.30)
project(hello_window VERSION 1.0.0)
#find_package(glfw3 REQUIRED)

add_executable(hello_window 
src/config.h  
src/function.cpp
src/make_texture.cpp
src/main.cpp 
src/glad.c)

target_include_directories(hello_window PRIVATE dependencies)
target_link_libraries(hello_window glfw3)