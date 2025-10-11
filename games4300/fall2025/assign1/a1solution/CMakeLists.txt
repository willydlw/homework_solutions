# SubProject assign1/CMakeLists.txt 
project(a1solution)

# specify binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})


# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Wextra -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code


# specify directory where compiler should look for header files
include_directories("include")


# create executables

add_executable(a1solution)
target_sources(a1solution PRIVATE 
    src/main.cpp
    src/gameConfig.cpp
    src/circle.cpp
    src/rectangle.cpp
    src/game.cpp
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
target_link_libraries(a1solution
    PRIVATE SFML::Graphics
    PRIVATE SFML::Window 
    PRIVATE SFML::System
    PRIVATE ImGui-SFML::ImGui-SFML
    PUBLIC  m
)

target_link_libraries(displayText
    PRIVATE SFML::Graphics 
)

# copy resource files to binary directories
set(SOURCE_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../assets")
set(DESTINATION_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets")
file(COPY ${SOURCE_ASSET_DIR}/ DESTINATION "${DESTINATION_ASSET_DIR}")
