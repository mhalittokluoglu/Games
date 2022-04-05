#include "Screen.hpp"
#include <thread>
#include "Logger.hpp"
#include "GLRelated/Shaders/ShaderSource/ShaderSources.hpp"
#include <chrono>
#include "GLRelated/Screen/Renderer/TetrominoRenderer.hpp"
#include "GLRelated/Screen/Renderer/ScreenRenderer.hpp"
#include <functional>

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
    m_CurrentTetromino = m_Engine.GetFirstTetro();
    std::function<void(Tetromino*)> TetroChangedCallback = std::bind(&Screen::TetrominoChanged, this, std::placeholders::_1);
    m_Engine.SetTetroChangedCallBack(TetroChangedCallback);
}

void Screen::ProcessScreen()
{
    {
        TetrominoRenderer renderer;
        renderer.Initialize(m_ShaderProgram);
        ScreenRenderer screenRenderer;
        screenRenderer.Initialize(m_ShaderProgram, m_Engine.GetMap());

        TetrisMath::IntPosition pos;
        while (!glfwWindowShouldClose(m_Window))
        {
            ProcessInput(m_Window);
            m_Engine.RunApplication();
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_ShaderProgram->Use();
            screenRenderer.DrawScreen();
            renderer.SetTetromino(*m_CurrentTetromino);
            renderer.DrawTetromino();
            // vao.Bind();
            // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }
    delete m_ShaderProgram;
    glfwTerminate();
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
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_Engine.DownKeyPressed();
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        m_Engine.RightKeyPressed();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        m_Engine.LeftKeyPressed();
    }
}

void Screen::TetrominoChanged(Tetromino *tetro)
{
    m_CurrentTetromino = tetro;
}