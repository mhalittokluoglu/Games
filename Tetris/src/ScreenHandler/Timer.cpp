#include "Timer.hpp"
#include <thread>
#include <chrono>
#include <mutex>

std::mutex m;

ScreenHandler *Timer::m_ScreenHandler = nullptr;

void Timer::InitiateTimer(ScreenHandler *handler)
{
    m_ScreenHandler = handler;
    std::thread *keyInputThread = new std::thread(&ListenForInputs); 
}

void Timer::ListenForInputs()
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        m.lock();
        m_ScreenHandler->TimeTick();
        m.unlock();
    }
}

void Timer::StartTimer()
{


}

