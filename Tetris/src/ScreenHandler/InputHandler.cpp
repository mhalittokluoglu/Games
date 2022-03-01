#include "InputHandler.hpp"
#include <thread>

ScreenHandler *InputHandler::m_ScreenHandler = nullptr;

void InputHandler::InitiateInputHandler(ScreenHandler *handler)
{
    m_ScreenHandler = handler;
    std::thread *keyInputThread = new std::thread(&ListenForInputs); 
}

void InputHandler::ListenForInputs()
{
    keypad(m_ScreenHandler->m_GameWindow, true);
    while (true)
    {
        int16_t key = wgetch(m_ScreenHandler->m_GameWindow);
        if (key == KEY_UP)
        {
            m_ScreenHandler->UpKeyPressed();
        }
        else if (key == KEY_DOWN)
        {
            m_ScreenHandler->DownKeyPressed();
        }
        else if (key == KEY_RIGHT)
        {
            m_ScreenHandler->RightKeyPressed();
        }
        else if (key == KEY_LEFT)
        {
            m_ScreenHandler->LeftKeyPressed();
        }
    }
}

void InputHandler::StartTimer()
{


}

