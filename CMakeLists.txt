cmake_minimum_required(VERSION 3.7)
project(settlers_of_catan)

set(CMAKE_CXX_STANDARD 11)

include_directories(source)

add_definitions(-DSOC_DEBUG)

set(SOURCE_FILES
        source/platform/linux_socatan_main.cpp
        source/socatan.cpp
        source/socatan.h
        source/socatan_types.h
        source/socatan_util.h
        source/socatan_input.h
        source/socatan_debug.h
        source/socatan_memory.cpp
        source/socatan_memory.h
        source/socatan_render.cpp
        source/socatan_render.h
        source/socatan_math.cpp
        source/socatan_math.h
        source/socatan_opengl.h
        source/socatan_opengl.cpp source/socatan_platform.cpp source/socatan_platform.h)
add_executable(settlers_of_catan ${SOURCE_FILES})
target_link_libraries(settlers_of_catan GL X11)
