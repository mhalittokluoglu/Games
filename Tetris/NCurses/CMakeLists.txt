cmake_minimum_required(VERSION 3.22)

project(Tetris)
add_executable(${PROJECT_NAME} src/Main.cpp 
src/Game/Game.hpp
src/Game/Game.cpp
src/Game/Timer.hpp
src/Game/Timer.cpp
src/Tetrominos/TetrominosGenerator.hpp
src/Tetrominos/TetrominosGenerator.cpp
src/Tetrominos/Tetrominos.hpp
src/Tetrominos/Tetrominos.cpp
)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} ncurses Threads::Threads)