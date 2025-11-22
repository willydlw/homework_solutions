# SubProject assign2/CMakeLists.txt
project(a3solution)

# specify binary output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

# set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++20 -Wall -Wextra -Werror -pedantic")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)   # optional: Set to OFF for more portable code


set(SRC_FILES
    src/main.cpp
    src/Assets.cpp
    src/GameEngine.cpp
    src/Scene_Menu.cpp
    src/Scene_Play.cpp
    include/Action.hpp
    include/Animation.hpp
    include/Components.hpp
    include/Entity.hpp 
    include/EntityManager.hpp
    include/Physics.hpp 
    include/Vec2.hpp
)

# executable
set(exec_name a3)
add_executable(${exec_name} ${SRC_FILES})
target_link_libraries(${exec_name}
    PRIVATE SFML::Graphics
    PRIVATE ImGui-SFML::ImGui-SFML
    PUBLIC  m
)

include_directories("include")


# copy resource files to binary directories
#set(SOURCE_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
#set(DESTINATION_ASSET_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")

#file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets")
#file(COPY ${SOURCE_ASSET_DIR}/ DESTINATION "${DESTINATION_ASSET_DIR}")

