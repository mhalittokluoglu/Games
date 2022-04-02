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
src/GLRelated/Screen/Renderer/Rectangle.hpp
src/GLRelated/Screen/Renderer/Rectangle.cpp
src/GLRelated/Screen/Renderer/TetrominoRenderer.hpp
src/GLRelated/Screen/Renderer/TetrominoRenderer.cpp
src/GLRelated/Screen/Renderer/ScreenRenderer.hpp
src/GLRelated/Screen/Renderer/ScreenRenderer.cpp
src/GLRelated/Screen/Screen.hpp
src/GLRelated/Screen/Screen.cpp
src/TetrisEngine/Tetromino/TetrominoData.hpp
src/TetrisEngine/Tetromino/TetrominoData.cpp
src/TetrisEngine/Tetromino/ITetromino.hpp
src/TetrisEngine/Tetromino/Tetromino.hpp
src/TetrisEngine/Tetromino/Tetromino.cpp
src/TetrisEngine/MathLib/TetrisMath.hpp
src/TetrisEngine/MathLib/TetrisMath.cpp
)

option(LOG_ENABLED "Log Enabled Option" ON)
option(LINUX_SYSTEM "Linux System" ON)
option(WINDOWS_SYSTEM "Windows System" OFF)

if (LINUX_SYSTEM)
add_compile_definitions(LINUX_SYSTEM)
endif()

if (WINDOWS_SYSTEM)
add_compile_definitions(WINDOWS_SYSTEM)
endif()


add_subdirectory(vendor/glfw)
target_link_libraries(${PROJECT_NAME} glfw)
target_include_directories(${PROJECT_NAME} PUBLIC vendor/glfw/include)

add_subdirectory(src/Logger)
target_link_libraries(${PROJECT_NAME} Logger)
target_link_directories(${PROJECT_NAME} PUBLIC Logger)

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC src/Logger)

find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} Threads::Threads)

# GLAD
target_include_directories(${PROJECT_NAME} PUBLIC vendor/glad/include)
