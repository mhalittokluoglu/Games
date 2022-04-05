#include "GLRelated/Screen/Screen.hpp"
#include "Logger.hpp"

int main()
{
    Logger::InitLogger("127.0.0.1", 30000);
    TetrisMath::SetScreenValues(0.02f, 0.02f, 30, 20, 0.8f);
    Screen screen(800, 600);
    screen.ProcessScreen();
}
