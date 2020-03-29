cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mage)
add_executable(mage src/mage.cpp)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

add_dependencies(mage OpenGL::OpenGL)

target_link_libraries(mage OpenGL::OpenGL glfw glm)
