cmake_minimum_required(VERSION 3.28)
project(Games4300 LANGUAGES CXX)


add_subdirectory(dependencies)
add_subdirectory(assign1)


# Optionally set global compile definitions or flags
# add_compile_definitions(GLOBAL_DEF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code