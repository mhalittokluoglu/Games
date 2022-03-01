#include "ScreenHandler/ScreenHandler.hpp"
#include "ScreenHandler/InputHandler.hpp"
int main()
{
    ScreenHandler handler;
    handler.Start();
    // InputHandler::InitiateInputHandler(handler);

    getch();
    // while(true);
}