cmake_minimum_required(VERSION 3.20)
set(CMAKE_VS_GLOBALS "VcpkgEnabled=false")
project(the-void-engine)

find_package(SDL3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)
find_package(imgui REQUIRED)

add_executable(VoidEngine 
    game/main.cpp
    engine/Window.cpp
    engine/Window.hpp
    engine/Input.hpp
    engine/Input.cpp
    engine/Renderer.hpp
    engine/Renderer.cpp
    third_party/imgui/bindings/imgui_impl_sdl3.cpp
    third_party/imgui/bindings/imgui_impl_opengl3.cpp
)

target_link_libraries(VoidEngine PRIVATE SDL3::SDL3 glad::glad glm::glm imgui::imgui)
target_include_directories(VoidEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} third_party/imgui/bindings)