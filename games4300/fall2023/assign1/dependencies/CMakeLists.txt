include(FetchContent)

# SFML
FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
)
add_subdirectory(sfml)

# Dear ImGui
FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
  GIT_TAG master
)

FetchContent_MakeAvailable(imgui)

# ImGui-SFML
FetchContent_Declare(
  imgui-sfml
  GIT_REPOSITORY https://github.com/SFML/imgui-sfml
  GIT_TAG 2.6.x
)
add_subdirectory(imgui-sfml)
