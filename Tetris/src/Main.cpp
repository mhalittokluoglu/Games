#include "ScreenHandler/ScreenHandler.hpp"
#include "ScreenHandler/Timer.hpp"
int main()
{
    ScreenHandler handler(30, 25);
    handler.Start();
    Timer::InitiateTimer(&handler);
    handler.RunInputEvents();
    getch();
    // while(true);
}