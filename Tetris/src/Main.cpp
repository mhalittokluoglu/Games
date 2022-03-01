#include "ScreenHandler/ScreenHandler.hpp"
#include "ScreenHandler/Timer.hpp"
int main()
{
    ScreenHandler handler;
    handler.Start();
    Timer::InitiateTimer(&handler);
    handler.RunInputEvents();
    getch();
    // while(true);
}