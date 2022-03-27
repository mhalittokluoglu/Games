#include "Screen.hpp"
#include <thread>
#include "Logger.hpp"
#include "GLRelated/Shaders/ShaderSource/ShaderSources.hpp"

Screen::Screen(uint32_t width, uint32_t height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_Window = glfwCreateWindow(width, height, "Tetris", NULL, NULL);

    if (!m_Window)
    {
        Logger::LOG_FATAL("Failed to create GLFW window!");
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_Window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        Logger::LOG_FATAL("Failed to Initialize GLAD");
        return;
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(m_Window, FrameBufferSizeCallBack);
    Shader vertexShader(ShaderSources::vertexShaderSource, GL_VERTEX_SHADER);
    Shader fragmentShader(ShaderSources::fragmentShaderSource, GL_FRAGMENT_SHADER);
    m_ShaderProgram = new ShaderProgram();
    m_ShaderProgram->AttachShader(vertexShader);
    m_ShaderProgram->AttachShader(fragmentShader);
    m_ShaderProgram->Link();
}

void Screen::ProcessScreen()
{
    while (!glfwWindowShouldClose(m_Window))
    {
        ProcessInput(m_Window);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_ShaderProgram->Use();
        ShapesMutex.lock();
        for (uint32_t i = 0; i < m_Shapes.size(); i++)
        {
            m_ShaderProgram->SetFloat3("shapeColor", m_Shapes[i]->Color());
            if (m_Shapes[i]->IsMoving())
            {
                m_Shapes[i]->UpdateLocation();
            }
            m_Shapes[i]->Draw();
        }
        ShapesMutex.unlock();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
    for (uint32_t i = 0; i < m_Shapes.size(); i++)
    {
        delete m_Shapes[i];
    }
    delete m_ShaderProgram;
    glfwTerminate();
}

void Screen::AddShape(Shapes::IShape *shape)
{
    m_Shapes.push_back(shape);
}

void Screen::FrameBufferSizeCallBack(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Screen::ProcessInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}