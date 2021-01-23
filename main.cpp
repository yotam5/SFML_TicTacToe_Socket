
#include "./source/Game.cpp"
#include <iostream>
//FIXME: MSGPACK FUCKING CANT SEND ZERO

/*
    NOTE: compile: g++ main.cpp -o sfml-app.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
*/

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        Game game;
        game.run();
    }
    else
    {
        if (argc > 1)
        {
            Game game(*argv[1]);
            game.run();
        }
    }
    //std::cout << game.clickToPos(350) << " " << game.clickToPos(50);
}