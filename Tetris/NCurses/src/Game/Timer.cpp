#include "Timer.hpp"
#include <thread>
#include <chrono>
#include <mutex>

std::mutex m;

Game *Timer::m_Game = nullptr;

void Timer::InitiateTimer(Game *game)
{
    m_Game = game;
    std::thread *keyInputThread = new std::thread(&ListenForInputs); 
}

void Timer::ListenForInputs()
{
    m.lock();
    bool isGameRunning = m_Game->GetIsGameRunning();
    m.unlock();
    while (isGameRunning)
    {
        uint64_t score = m_Game->GetScore();
        std::this_thread::sleep_for(std::chrono::milliseconds((300 - score * 10)));
        m.lock();
        (200 - score *2);
        m_Game->TimeTick();
        bool isGameRunning = m_Game->GetIsGameRunning();
        m.unlock();
    }
}


