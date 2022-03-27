#ifndef _TIMER_HPP_
#define _TIMER_HPP_
#include "Game.hpp"
class Timer
{
public:
    static void SetGame(Game *handler);
    static void ListenForInputs();
    static void StartTimer();
    static void InitiateTimer(Game *handler);
private:
    static Game *m_Game;
};
#endif