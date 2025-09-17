# Project name (can be different from directory name)
project(GWARS)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

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
    src/config.cpp
    src/circle.cpp
    src/rectangle.cpp
)


# Link to other libraries (if needed)
# PUBLIC m links math library
target_link_libraries(demo 
    PRIVATE SFML::Graphics 
    PRIVATE ImGui-SFML::ImGui-SFML
    PUBLIC m)

target_link_libraries(assign1
    PRIVATE SFML::Graphics
    PRIVATE ImGui-SFML::ImGui-SFML
)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/fonts")
file(COPY fonts/ DESTINATION "${CMAKE_BINARY_DIR}/bin/fonts")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/bin/config")
file(COPY config/ DESTINATION "${CMAKE_BINARY_DIR}/bin/config")
