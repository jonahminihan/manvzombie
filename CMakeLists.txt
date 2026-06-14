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
        simple_render_system.cpp
        mvz_camera.hpp
        mvz_camera.cpp
        keyboard_movement_controller.hpp
        keyboard_movement_controller.cpp
        mvz_utils.hpp
        mvz_game_object.cpp
        mvz_buffer.hpp
        mvz_buffer.cpp
        mvz_frame_info.hpp
        mvz_descriptors.hpp
        mvz_descriptors.cpp)

add_dependencies(manvzombie CompileShaders)

target_link_libraries(manvzombie glfw)
target_link_libraries(manvzombie Vulkan::Vulkan)
include_directories("/opt/homebrew/include")
include_directories("/Users/jonah/dev/libs/tinyobjloader")
link_directories("/opt/homebrew/lib")
link_directories("/Users/jonah/dev/libs/tinyobjloader")

