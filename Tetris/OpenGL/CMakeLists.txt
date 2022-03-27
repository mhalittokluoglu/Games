cmake_minimum_required(VERSION 3.16)

project (Tetris)

add_executable(${PROJECT_NAME} 
src/MainApplication.cpp
vendor/glad/src/glad.c
src/GLRelated/Shaders/Shader.hpp
src/GLRelated/Shaders/Shader.cpp
src/GLRelated/Shaders/ShaderProgram.hpp
src/GLRelated/Shaders/ShaderProgram.cpp
src/GLRelated/Shaders/ShaderSource/ShaderSources.hpp
src/GLRelated/Vertex/VertexBuffer.hpp
src/GLRelated/Vertex/VertexBuffer.cpp
src/GLRelated/Vertex/VertexArray.hpp
src/GLRelated/Vertex/VertexArray.cpp
src/GLRelated/Vertex/ElementBuffer.hpp
src/GLRelated/Vertex/ElementBuffer.cpp
src/GLRelated/MatData.hpp
src/GLRelated/Screen/Screen.hpp
src/GLRelated/Screen/Screen.cpp
src/GLRelated/Screen/Shapes/Rectangle.hpp
src/GLRelated/Screen/Shapes/Rectangle.cpp
src/GLRelated/Screen/Shapes/IShape.hpp
)

add_subdirectory(src/Logger)

target_link_libraries(${PROJECT_NAME} Logger)
target_link_directories(${PROJECT_NAME} PUBLIC Logger)

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC src/Logger)

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} GL GLU X11 Xrandr dl Xi glfw Threads::Threads)

# GLAD
target_include_directories(${PROJECT_NAME} PUBLIC vendor/glad/include)
