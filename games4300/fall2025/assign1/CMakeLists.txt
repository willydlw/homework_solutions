# SubProject assign1/CMakeLists.txt 
project(assign1)

# specify binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code


# specify directory where compiler should look for header files
include_directories("include")


# create executables
add_executable(a1demo)
target_sources(a1demo PRIVATE 
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

add_executable(displayText)
target_sources(displayText PRIVATE 
    src/displayText.cpp
)


# Link to other libraries (if needed)
# PUBLIC m links math library
target_link_libraries(a1demo
    PRIVATE SFML::Graphics 
    PRIVATE ImGui-SFML::ImGui-SFML
    PUBLIC m)

target_link_libraries(assign1
    PRIVATE SFML::Graphics
    PRIVATE SFML::Window 
    PRIVATE SFML::System
    PRIVATE ImGui-SFML::ImGui-SFML
)

target_link_libraries(displayText
    PRIVATE SFML::Graphics 
)


# copy resource filed to binary directory
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/fonts")
file(COPY fonts/ DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/fonts")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config")
file(COPY config/ DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config")
