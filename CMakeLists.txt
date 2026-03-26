cmake_minimum_required(VERSION 3.10.0)
project(Alpheus VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)


find_package(OpenGL REQUIRED)

add_executable(Alpheus src/main.cpp src/glad.h src/glad.c)

target_link_libraries(Alpheus glfw OpenGL::GL)