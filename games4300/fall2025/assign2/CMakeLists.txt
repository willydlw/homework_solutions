# SubProject assign2/CMakeLists.txt
project(assign2)

# specify binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17 -Wall -Wextra -pedantic -Wno-unused-parameter -Wno-unused-variable")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code


include_directories("include")

# create executables
add_executable(assign2)
target_sources(assign2 PUBLIC 
    src/main.cpp
    src/Game.cpp
    include/Components.hpp 
    include/Entity.hpp
    include/EntityManager.hpp
    include/Vec2.hpp
)


# Link to other libraries
# PUBLIC m links math library
target_link_libraries(assign2
    PRIVATE SFML::Graphics
    PRIVATE ImGui-SFML::ImGui-SFML
    PUBLIC  m
)

# copy resource filed to binary directory
#file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/fonts")
#file(COPY fonts/ DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/fonts")

#file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config")
#file(COPY config/ DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/config")

