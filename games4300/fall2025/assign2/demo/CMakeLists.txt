# Project name (can be different from directory name)
project(ASSIGN2)

# specify output directory for binary executable files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code

# include Directory path
include_directories("include")


add_executable(assign2)
target_sources(assign2 PRIVATE 
    src/main.cpp
    src/Game.cpp
    include/Vec2.hpp
    include/Entity.hpp
    include/EntityManager.hpp
    include/Components.hpp
)

target_link_libraries(assign2
    PRIVATE SFML::Graphics
    PRIVATE SFML::Window 
    PRIVATE SFML::System
    PRIVATE ImGui-SFML::ImGui-SFML
)


#file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/fonts")
#file(COPY fonts/ DESTINATION "${CMAKE_BINARY_DIR}/bin/fonts")

#file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/config")
#file(COPY config/ DESTINATION "${CMAKE_BINARY_DIR}/bin/config")
