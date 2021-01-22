
#pragma once

#define WIDTH 600
#define HEIGHT 600

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <msgpack.hpp>
#include <string>
//-----------------------
#include "../source/O_X.cpp"
#include "../source/Board.cpp"
#include "../source/NetHelper.cpp"

#define PORT 2001

class Game
{
public:
    Game();

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
    
    Board board;
    bool endgame;
    bool moved;
    std::pair<int,int> lastPos;
    Players player; //FIXME
    NetHelper netHandle;
    bool sent;
    void initVariables();
    void initWindow();
    void loadTexture();
    void pollEvents();
    void render();
};