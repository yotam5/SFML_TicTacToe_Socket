
#pragma once

#include "../header/O_X.h"
#include <iostream>

std::array<sf::Texture *, 2> O_X::textures;
bool O_X::init = false;

O_X::O_X(Players player, int row, int column)
{
    if (!init)
    {
        loadTextures();
        init = true;
    }
    this->changePos(row, column);
    this->changeScreenPos();
    this->sprite.setTexture(*textures[static_cast<int>(player)]);
    this->type = player;
}

O_X::~O_X()
{
}

void O_X::changePos(int row, int column)
{
    this->pos.first = row;
    this->pos.second = column;
}

void O_X::render(sf::RenderTarget &target)
{
    target.draw(this->sprite);
}

void O_X::loadTextures()
{
    textures[0] = new sf::Texture; //O
    if (!textures[0]->loadFromFile("./asserts/o.png"))
    {
        throw std::invalid_argument("couldnt load O\n");
    }

    textures[1] = new sf::Texture; //X
    if (!textures[1]->loadFromFile("./asserts/x.png"))
    {
        throw std::invalid_argument("couldnt load X\n");
    }
}

Players O_X::getType() const
{
    return this->type;
}

std::pair<int,int> O_X::getPos() const
{
    return this->pos;
}

void O_X::changeScreenPos()
{
    auto p1 = this->pos.first * 205 + 30;
    auto p2 = this->pos.second * 205 + 30;
    this->sprite.setPosition(p1, p2);
}