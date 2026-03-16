cmake_minimum_required(VERSION 3.20)

project(the-void-engine)

find_package(SDL3 REQUIRED)
find_package(glad REQUIRED)
find_package(glm REQUIRED)

add_executable(VoidEngine 
    game/main.cpp
    engine/Window.cpp
    engine/Window.hpp
    engine/Renderer.hpp
    engine/Renderer.cpp
)

target_link_libraries(VoidEngine PRIVATE SDL3::SDL3 glad::glad glm::glm)
target_include_directories(VoidEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})