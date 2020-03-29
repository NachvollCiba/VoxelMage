cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mage)
add_executable(mage src/mage.cpp)

# disable glfw tests, examples and documentation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glm REQUIRED)

add_dependencies(mage OpenGL::OpenGL)

target_link_libraries(mage OpenGL::OpenGL glfw glm)
