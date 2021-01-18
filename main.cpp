
#include "./source/Game.cpp"
#include <iostream>

/*
    NOTE: compile: g++ main.cpp -o sfml-app.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
*/

int main()
{
    Game game;

    game.run();
    //std::cout << game.clickToPos(350) << " " << game.clickToPos(50);
}