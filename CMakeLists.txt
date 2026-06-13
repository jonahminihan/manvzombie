cmake_minimum_required(VERSION 4.2)
project(manvzombie)

set(CMAKE_CXX_STANDARD 20)
find_package(glfw3 3.4 REQUIRED)
find_package(Vulkan REQUIRED)

add_custom_target(CompileShaders
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_SOURCE_DIR}/compile.sh
        COMMENT "Building Shaders..."
)

add_executable(manvzombie main.cpp
        mvz_window.hpp
        mvz_window.cpp
        main_app.hpp
        main_app.cpp
        mvz_pipeline.hpp
        mvz_pipeline.cpp
        mvz_device.hpp
        mvz_device.cpp
        mvz_swap_chain.hpp
        mvz_swap_chain.cpp
        mvz_model.hpp
        mvz_model.cpp
        mvz_game_object.hpp
        mvz_renderer.hpp
        mvz_renderer.cpp
        simple_render_system.hpp
        simple_render_system.cpp)

add_dependencies(manvzombie CompileShaders)

target_link_libraries(manvzombie glfw)
target_link_libraries(manvzombie Vulkan::Vulkan)
include_directories("/opt/homebrew/include")
link_directories("/opt/homebrew/lib")

