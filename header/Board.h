
#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include "../source/O_X.cpp"

#define SIDE 3

class Board
{
public:
    Board();
    ~Board();
    bool isWinner();
    void renderBoard(sf::RenderTarget &window);
    bool isEmpty(int row, int pos) const;
    void setPiece(int row, int column, Players player = Players::CAPITAL_O);
    static int clickToPos(double);
    std::vector<std::pair<int,int>> getWinnerPoses() const;
private:
    void initBoard();
    std::array<std::array<O_X *, 3>, 3> boardArr;
    std::vector < std::pair<int, int> > winnerPoses;
    bool winner;
};