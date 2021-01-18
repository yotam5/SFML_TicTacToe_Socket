
#pragma once

#include "../header/Board.h"

Board::Board()
{
    this->initBoard();
    this->setPiece(0, 0);
}

Board::~Board()
{
    for (auto texture : this->textures)
    {
        delete texture.second;
    }
    for (int i = 0; i < SIDE; ++i)
    {
        for (int k = 0; k < SIDE; ++k)
        {
            delete this->boardArr[i][k];
        }
    }
}

bool Board::isWinner() const
{
    int row;
    int column;
    int count = 0;

    bool mode = true; //up down
    for (int i = 0; i < 2; i++)
    {
        for (row = 0; row < 3; row++)
        {
            int counter = 0;
            if (this->boardArr[(mode) ? row : column][0] == nullptr)
            {
                continue;
            }
            Players tmp = this->boardArr[row][0]->getType();
            for (column = 0; column < 3; column++)
            {
                if (this->boardArr[(mode) ? row : column][(mode) ? column : row] == nullptr ||
                    this->boardArr[(mode) ? row : column][(mode) ? column : row]->getType() != tmp)
                {
                    break;
                }
                counter++;
            }
            if (counter == 3)
            {
                return true;
            }
        }
        mode = false; //right left
    }
    std::array<std::pair<int, int>, 3> op1 = {std::make_pair(1, 1), std::make_pair(0, 0), std::make_pair(2, 2)};
    std::array<std::pair<int, int>, 3> op2 = {std::make_pair(1, 1), std::make_pair(2, 0), std::make_pair(0, 2)};
    auto combine = {op1, op2};
    auto middle = this->boardArr[1][1];
    if (middle == nullptr)
    {
        return false;
    }
    for (auto op : combine)
    {
        int count = 0;
        for (auto p : op)
        {
            if(this->boardArr[p.first][p.second] != nullptr
                && this->boardArr[p.first][p.second]->getType() == middle->getType())
            {
                count++;
                continue;
            }
            break;
        }
        if(count == 3){
            return true;
        }
    }

    return false;
}

int Board::clickToPos(double value)
{
    if (value < 0 || value > 600)
    {
        return -1;
    }
    int key = (int)value;
    int loc = 0;
    for (int i = 195; i < 600 && key >= i; i += 195)
    {
        ++loc;
    }
    return loc;
}

void Board::setPiece(int row, int column, Players player)
{
    if (this->isEmpty(row, column))
    {
        this->boardArr[row][column] = new O_X(player, row, column);
    }
}

void Board::loadTexture()
{
}

bool Board::isEmpty(int row, int column) const
{
    return this->boardArr[row][column] == nullptr;
}

void Board::initBoard()
{
    for (int i = 0; i < SIDE; ++i)
    {
        for (int k = 0; k < SIDE; ++k)
        {
            this->boardArr[i][k] = nullptr;
        }
    }
}

void Board::renderBoard(sf::RenderTarget &window)
{
    for (int i = 0; i < SIDE; ++i)
    {
        for (int k = 0; k < SIDE; ++k)
        {
            if (this->boardArr[i][k] != nullptr)
            {
                this->boardArr[i][k]->render(window);
            }
        }
    }
}