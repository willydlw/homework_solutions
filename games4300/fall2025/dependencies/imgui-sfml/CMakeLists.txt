message(STATUS "Fetching ImGui-SFML...")

set(IMGUI_DIR ${imgui_SOURCE_DIR})
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SMFL_IMGUI_DEMO ON)

FetchContent_MakeAvailable(imgui-sfml)