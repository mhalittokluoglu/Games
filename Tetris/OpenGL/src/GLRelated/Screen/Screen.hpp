#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "Shapes/IShape.hpp"
#include <mutex>
#include <inttypes.h>
#include <vector>
#include "GLRelated/Shaders/ShaderProgram.hpp"
class Screen
{
public:
    Screen(uint32_t width, uint32_t height);
    void AddShape(Shapes::IShape *shape);
    void ProcessScreen();

private:
    void ProcessInput(GLFWwindow *window);
    static void FrameBufferSizeCallBack(GLFWwindow* window, int width, int height);
    std::mutex ShapesMutex;
    std::vector<Shapes::IShape*> m_Shapes;
    GLFWwindow *m_Window;
    ShaderProgram *m_ShaderProgram;
};
#endif