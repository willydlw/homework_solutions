# Project name (can be different from directory name)
project(GWARS)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code

# Include Directories 
include_directories("include")

# create executable or library 
add_executable(demo)
target_sources(demo PRIVATE 
    src/demo.cpp
)

add_executable(assign1)
target_sources(assign1 PRIVATE 
    src/main.cpp
    src/gameConfig.cpp
    src/circle.cpp
    src/rectangle.cpp
    src/game.cpp
)

add_executable(workDir)
target_sources(workDir PRIVATE 
    src/printWorkingDirectory.cpp
)

add_executable(findFile)
target_sources(findFile PRIVATE 
    src/findFile.cpp
)


# Link to other libraries (if needed)
# PUBLIC m links math library
target_link_libraries(demo 
    PRIVATE SFML::Graphics 
    PRIVATE ImGui-SFML::ImGui-SFML
    PUBLIC m)

target_link_libraries(assign1
    PRIVATE SFML::Graphics
    PRIVATE SFML::Window 
    PRIVATE SFML::System
    PRIVATE ImGui-SFML::ImGui-SFML
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Wextra -pedantic")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/fonts")
file(COPY fonts/ DESTINATION "${CMAKE_BINARY_DIR}/bin/fonts")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/config")
file(COPY config/ DESTINATION "${CMAKE_BINARY_DIR}/bin/config")
