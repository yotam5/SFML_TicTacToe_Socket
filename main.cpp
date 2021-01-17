
#include "./source/Game.cpp"

/*
    NOTE: compile: g++ main.cpp -o sfml-app.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
*/

int main()
{
    Game game;

    game.run();
}