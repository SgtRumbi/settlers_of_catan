cmake_minimum_required(VERSION 3.7)
project(settlers_of_catan)

set(CMAKE_CXX_STANDARD 11)

include_directories(source)

add_definitions(-DSOC_DEBUG)

set(SOURCE_FILES
        source/platform/linux_socatan_main.cpp
        source/socatan.cpp
        source/socatan.h
        source/socatan_types.h source/socatan_util.h source/socatan_input.h)
add_executable(settlers_of_catan ${SOURCE_FILES})
