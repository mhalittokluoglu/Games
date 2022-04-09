#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <vector>
#include "GLRelated/Shaders/ShaderProgram.hpp"
#include "TetrisEngine/Engine.hpp"

class Screen
{
public:
    Screen(uint32_t width, uint32_t height);
    void ProcessScreen();
    void TetrominoChanged(Tetromino *currentTetro, Tetromino *nextTetro);

private:
    Engine m_Engine;
    void ProcessInput(GLFWwindow *window);
    void ProcessTimer();
    static void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);
    GLFWwindow *m_Window;
    ShaderProgram *m_ShaderProgram;
    Tetromino *m_CurrentTetromino;
    Tetromino *m_NextTetromino;
    

};
#endif