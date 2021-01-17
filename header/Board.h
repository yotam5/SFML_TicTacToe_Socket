
#pragma once

enum class Players
{
    CAPITAL_O = 1,
    CAPITAL_X = 2
};

#include <array>

class Board
{
public:
    bool isWinner() const;
    bool isLegal(int, int) const;
    void move(int, int, Players);

private:
    std::array<std::array<int, 3>, 3> boardArr;
};