cmake_minimum_required(VERSION 3.10)
project(Alpheus VERSION 0.1.0 LANGUAGES C CXX)

cmake_policy(SET CMP0072 NEW)

# Executable
add_executable(Alpheus 
    src/main.cpp 
    "src/renderer/window.cpp"
    "src/renderer/renderer.cpp"
    "src/renderer/loader.cpp"
    src/glad.c
 "src/renderer/shader.cpp" "include/shader.h" "include/texture.h" "src/texture.cpp" "src/tools/stb_image.cpp" "src/entites/camera.cpp"  "include/camera.h" "include/entity.h"     "include/light.h" "include/input.h" "src/tools/input.cpp"  "include/tools.h" "src/tools/tools.cpp")

# Include directories (modern way)
target_include_directories(Alpheus PRIVATE include)

# OpenGL
find_package(OpenGL REQUIRED)

# Link
target_link_libraries(Alpheus 
    PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.lib"
    OpenGL::GL
)

# Copy DLL
add_custom_command(TARGET Alpheus POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw3.dll"
    $<TARGET_FILE_DIR:Alpheus>
)