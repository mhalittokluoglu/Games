#ifndef _INPUTHANDLER_HPP_
#define _INPUTHANDLER_HPP_
#include "ScreenHandler.hpp"
class InputHandler
{
public:
    static void SetScreenHandler(ScreenHandler *handler);
    static void ListenForInputs();
    static void StartTimer();
    static void InitiateInputHandler(ScreenHandler *handler);
private:
    static ScreenHandler *m_ScreenHandler;
};
#endif