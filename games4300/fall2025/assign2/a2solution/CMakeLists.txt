# SubProject assign2/CMakeLists.txt
project(a2solution)

add_subdirectory(test)

# specify binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code


include_directories("include")

# create executables
add_executable(a2solution)
target_sources(a2solution PUBLIC 
    src/main.cpp
)


# Link to other libraries
# PUBLIC m links math library
target_link_libraries(a2solution
    PRIVATE SFML::Graphics
    PRIVATE ImGui-SFML::ImGui-SFML
    PUBLIC  m
)

# copy resource filed to binary directory
#file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/fonts")
#file(COPY ../fonts/ DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/fonts")

#file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config")
#file(COPY ../config/ DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config")

