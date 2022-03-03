#include "Game/Game.hpp"
#include "Game/Timer.hpp"
int main()
{
    Game game(30, 25);
    game.Start();
    Timer::InitiateTimer(&game);
    game.RunInputEvents();
}