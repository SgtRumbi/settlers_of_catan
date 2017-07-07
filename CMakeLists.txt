cmake_minimum_required(VERSION 3.0.2)
project(settlers_of_catan)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(source)

add_definitions(-DSOC_DEBUG)

set(SOURCE_FILES
        source/platform/linux_socatan_main.cpp
        source/socatan.cpp
<<<<<<< HEAD
	source/socatan_render.cpp)
        # source/socatan.h
        # source/socatan_types.h 
	# source/socatan_util.h 
	# source/socatan_input.h)
=======
        source/socatan.h
        source/socatan_types.h
        source/socatan_util.h
        source/socatan_input.h source/socatan_debug.h source/socatan_memory.cpp source/socatan_memory.h)
>>>>>>> adfbfeeb27d93c12122279171cbd86c643864c58
add_executable(settlers_of_catan ${SOURCE_FILES})
target_link_libraries(settlers_of_catan GL X11)
