#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <inttypes.h>
#include <vector>
#include "GLRelated/Shaders/ShaderProgram.hpp"
class Screen
{
public:
    Screen(uint32_t width, uint32_t height);
    void ProcessScreen();

private:
    void ProcessInput(GLFWwindow *window);
    void ProcessTimer();
    static void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);
    GLFWwindow *m_Window;
    ShaderProgram *m_ShaderProgram;
    int8_t m_xOffset;
    int8_t m_yOffset;
    int64_t m_Timer;
    int64_t m_LeftTimer;
    int64_t m_RightTimer;
    int64_t m_DownTimer;

    void SetValidForMove(int8_t xOffset, int8_t yOffset);
    void ResetMove();
    bool m_ValidForMove;
    bool ValidForMove();
    int64_t GetTimeInMilliSecond();

};
#endif