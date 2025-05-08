cmake_minimum_required(VERSION 3.28)
project(Snake C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES
    "src/**.c"
)

add_executable(Snake ${SOURCES})
target_include_directories(Snake PRIVATE "src")

add_custom_target(link_target ALL COMMAND ${CMAKE_COMMAND} -E create_symlink "${PROJECT_SOURCE_DIR}/shaders" "${PROJECT_BINARY_DIR}/shaders")

find_package(glfw3 REQUIRED)
target_link_libraries(Snake PRIVATE glfw)

add_subdirectory("ext/glad")
target_link_libraries(Snake PRIVATE Glad)
