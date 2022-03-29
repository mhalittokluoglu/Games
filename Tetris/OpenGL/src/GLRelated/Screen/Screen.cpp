#include "Screen.hpp"
#include <thread>
#include "Logger.hpp"
#include "GLRelated/Shaders/ShaderSource/ShaderSources.hpp"
#include <chrono>
#include "GLRelated/Screen/Renderer/TetrominoRenderer.hpp"
#include "GLRelated/Screen/Renderer/ScreenRenderer.hpp"

Screen::Screen(uint32_t width, uint32_t height)
{
    m_xOffset = 0;
    m_yOffset = 0;
    m_ValidForMove = false;
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
    m_Timer = GetTimeInMilliSecond();
    m_LeftTimer = GetTimeInMilliSecond();
    m_RightTimer = GetTimeInMilliSecond();
    m_DownTimer = GetTimeInMilliSecond();

    TetrisMath::SetScreenValues(0.02f, 0.02f, 30, 20, 0.8f);
    TetrisMath::GLPosition position;
    position.X = 0.4f;
    position.Y = 0.3f;
    TetrisMath::Color color;
    color.R = 0.4f;
    color.G = 0.6f;
    color.B = 0.4f;
    {
        //TetrominoRenderer renderer;
        //renderer.Initialize(m_ShaderProgram);
        ScreenRenderer screenRenderer;
        screenRenderer.Initialize(m_ShaderProgram);
        bool tetroMap[4][4] = {
            1, 0, 0, 0,
            1, 1, 0, 0,
            0, 1, 0, 0,
            0, 0, 0, 0
            };

        TetrisMath::IntPosition pos;
        //renderer.SetTetromino(tetroMap, pos, color);
        while (!glfwWindowShouldClose(m_Window))
        {
            ProcessInput(m_Window);
            ProcessTimer();
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            m_ShaderProgram->Use();
            screenRenderer.DrawScreen();
            // renderer.DrawTetromino();
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
    int64_t currentTime = GetTimeInMilliSecond();
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        if (currentTime - m_DownTimer > 50)
        {
            SetValidForMove(0, -1);
            m_DownTimer = currentTime;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        if (currentTime - m_RightTimer > 50)
        {
            SetValidForMove(1, 0);
            m_RightTimer = currentTime;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        if (currentTime - m_LeftTimer > 50)
        {
            SetValidForMove(-1, 0);
            m_LeftTimer = currentTime;
        }
    }
}

void Screen::ProcessTimer()
{
    int64_t currentTime = GetTimeInMilliSecond();
    int64_t offset = currentTime - m_Timer;
    bool bIsItTime = false;
    if (offset > 750)
    {
        bIsItTime = true;
        m_Timer = GetTimeInMilliSecond();
        SetValidForMove(0, -1);
    }
}

int64_t Screen::GetTimeInMilliSecond()
{
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::seconds;
    using std::chrono::system_clock;
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return millisec_since_epoch;
}

void Screen::SetValidForMove(uint8_t xOffset, uint8_t yOffset)
{
    m_ValidForMove = true;
    m_xOffset = xOffset;
    m_yOffset = yOffset;
}
void Screen::ResetMove()
{
    m_ValidForMove = false;
    m_xOffset = 0;
    m_yOffset = 0;
}

bool Screen::ValidForMove()
{
    return m_ValidForMove;
}
