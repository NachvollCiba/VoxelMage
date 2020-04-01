cmake_minimum_required(VERSION 3.17.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(mage)

set(ALL_SOURCES
	src/mage.cpp
	src/InputHandler.cpp
	src/InputHandler.h
	src/ShaderManager.cpp
	src/ShaderManager.h
	src/Camera.cpp
	src/Camera.h
	src/Renderer.cpp
	src/Renderer.h
)

add_executable(mage ${ALL_SOURCES})

# disable glfw tests, examples and documentation
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw)

add_subdirectory(libs/glew/build/cmake)
include_directories(libs/glew/include)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(glm REQUIRED)

add_dependencies(mage OpenGL::OpenGL)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(mage glew OpenGL::OpenGL glfw glm)
