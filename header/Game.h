
#pragma once

#define WIDTH 600
#define HEIGHT 600

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <string>

class Game
{
public:
    Game();
    virtual ~Game();

    void update();

    bool isOpen() const;

    void run();
private:
    std::map<std::string, sf::Texture *> textures;
    sf::RenderWindow *window;
    sf::Event event;
    sf::Font font;
    sf::Text uiText;
    sf::VideoMode videoMode;
    sf::Sprite background;
    
    void initVariables();
    void initWindow();
    void loadTexture();
    void pollEvents();
    void render();
};