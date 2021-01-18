
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <unordered_map>

enum class Players
{
    CAPITAL_O = 0,
    CAPITAL_X = 1
};

class O_X
{
public:
    O_X(Players, int p1 = 0, int p2 = 0);
    ~O_X();
    void changePos(int,int);
    void render(sf::RenderTarget &target);
    static void loadTextures();
    Players getType() const;
    std::pair<int,int> getPos() const;
    //static std::pair<double, double> arrPosToScreen(int, int);
private:
    void changeScreenPos();
    sf::Sprite sprite;
    std::pair<int, int> pos;
    static std::array<sf::Texture *, 2> textures;
    static bool init;
    Players type;
};