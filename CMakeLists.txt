cmake_minimum_required(VERSION 3.10)
project(Alpheus VERSION 0.1.0 LANGUAGES C CXX)

cmake_policy(SET CMP0072 NEW)

# 1. Automatically find all source files (.cpp and .c) in the src directory
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
    "src/*.c"
)

# 2. Automatically find all header files (.h and .hpp) in the include directory
file(GLOB_RECURSE HEADERS 
    "include/*.h" 
    "include/*.hpp"
)

# 3. Create the executable using the gathered lists
add_executable(Alpheus ${SOURCES} ${HEADERS})


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