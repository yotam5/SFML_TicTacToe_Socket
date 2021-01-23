
#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <array>
#include "../source/O_X.cpp"
#include <algorithm>

#define SIDE 3

class Board
{
public:
    Board();
    ~Board();
    bool isWinner() const;
    void loadTexture();
    void renderBoard(sf::RenderTarget &window);
    bool isEmpty(int row, int pos) const;
    void setPiece(int row, int column, Players player = Players::CAPITAL_O);
    static int clickToPos(double);
private:
    void initBoard();
    std::array<std::array<O_X *, 3>, 3> boardArr;
    std::map<std::string, sf::Texture *> textures;
};