#ifndef _TIMER_HPP_
#define _TIMER_HPP_
#include "ScreenHandler.hpp"
class Timer
{
public:
    static void SetScreenHandler(ScreenHandler *handler);
    static void ListenForInputs();
    static void StartTimer();
    static void InitiateTimer(ScreenHandler *handler);
private:
    static ScreenHandler *m_ScreenHandler;
};
#endif