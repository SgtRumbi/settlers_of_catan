cmake_minimum_required(VERSION 3.7)
project(settlers_of_catan)

set(CMAKE_CXX_STANDARD 11)

include_directories(source)

set(SOURCE_FILES
        source/platform/linux_main.cpp
        source/game.cpp
        source/game.h
        source/types.h)
add_executable(settlers_of_catan ${SOURCE_FILES})
