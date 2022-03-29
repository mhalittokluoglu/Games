#include "GLRelated/Screen/Screen.hpp"
#include "Logger.hpp"

int main()
{
    Logger::InitLogger("127.0.0.1", 30000);
    
    Screen screen(800, 600);
    screen.ProcessScreen();
}
