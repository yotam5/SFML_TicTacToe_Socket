
#pragma once

#define WIDTH 600
#define HEIGHT 600

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <msgpack.hpp>
#include <string>
#include <unistd.h>
//-----------------------
#include "../source/O_X.cpp"
#include "../source/Board.cpp"
#include "../source/NetHelper.cpp"

class Game
{
public:
    Game(char = 'o');

    virtual ~Game();

    void update();

    bool isOpen() const;

    void run();
    int clickToPos(double) const;
    void handleTurns();

private:
    std::map<std::string, sf::Texture *> textures;
    sf::RenderWindow *window;
    sf::Event event;
    sf::Font font;
    sf::Text uiText;
    sf::VideoMode videoMode;
    sf::Sprite background;
    sf::Packet packet;

    Board board;
    std::pair<int, int> lastPos;
    Players player;
    NetHelper netHandle;
    bool sent;
    bool endgame;
    bool moved;
    int moveCounter;

    bool isTie();
    void initVariables();
    void initWindow();
    void loadTexture();
    void pollEvents();
    void render();
};