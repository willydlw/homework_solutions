# SubProject assign2/CMakeLists.txt
project(tests)

# specify binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code


include_directories("include")

# create executables
add_executable(testVec2)
target_sources(testVec2 PUBLIC 
    src/testVec2.cpp 
    include/Vec2Test.hpp 
)

# PUBLIC m links math library
target_link_libraries(testVec2
    PUBLIC  m
)


add_executable(gameConfigTest)
target_sources(gameConfigTest PUBLIC 
    src/testGameConfig.cpp
    src/gameConfigTest.cpp 
    ../a2solution/src/gameConfig.cpp
)

target_link_libraries(gameConfigTest
    PRIVATE SFML::Graphics
)

# copy resource files to binary directories
set(SOURCE_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(DESTINATION_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets")
file(COPY ${SOURCE_ASSET_DIR}/ DESTINATION "${DESTINATION_ASSET_DIR}")
