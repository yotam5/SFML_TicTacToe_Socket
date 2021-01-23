
#pragma once

/*
NOTE:
    msgpack cant send c_str() that represent a zero(cuz it null probably),
    the solution is to use sf::Packet that can have the origianl string value
    in the name of god it took long time to find this
*/

#include "../header/Game.h"
#include <iostream>

Game::Game(char whatPlayer)
{
    if (whatPlayer != 'o' && whatPlayer != 'x')
    {
        std::cout << "wrong usage" << std::endl;
        exit(1);
    }
    this->player = (whatPlayer == 'o') ? Players::CAPITAL_O : Players::CAPITAL_X;
    this->loadTexture();
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
    for (auto texture : this->textures)
    {
        delete texture.second;
    }
}

void Game::initVariables()
{
    this->sent = false;
    this->background.setTexture(*this->textures["BOARD"]);
    this->endgame = false;
    this->lastPos = std::make_pair(1, 1);
    this->moved = false;
}

void Game::initWindow()
{
    this->videoMode.height = HEIGHT;
    this->videoMode.width = WIDTH;
    this->window = new sf::RenderWindow(this->videoMode, "TicTacToe",
                                        sf::Style::Titlebar | sf::Style::Close);
    //init frame rate
    this->window->setFramerateLimit(60); //limit frame rate and make game playable

    //center
    auto desktop = sf::VideoMode::getDesktopMode();
    auto center = sf::Vector2i(desktop.width / 4, desktop.height / 4); //for center becuse it set top left
    window->setPosition(center);
}

bool Game::isOpen() const
{
    return this->window->isOpen();
}

void Game::update()
{
    this->pollEvents();
    if (this->moved)
    {
        //std::cout << "moved\n";istttt
        if (!this->sent)
        {
            this->netHandle.sendMsg<std::pair<int, int>>(this->lastPos);
            this->sent = true;
            this->moved = false;
        }
    }
    else if (!this->moved)
    {
        if (this->netHandle.getFullyRecive())
        {
            auto msgCopy = this->netHandle.getMsgCopy();
            auto oh1 = msgpack::unpack(msgCopy.data(), msgCopy.size());
            msgpack::object deserialized = oh1.get();
            std::pair<int,int> strtest = deserialized.as<std::pair<int,int>>();
            this->board.setPiece(strtest.first, strtest.second,
                                 (this->player == Players::CAPITAL_O) ? Players::CAPITAL_X : Players::CAPITAL_O);
            netHandle.setFullyRecive(false);
            this->sent = false;
        }
    }
}

void Game::render()
{
    this->window->clear();
    this->window->draw(this->background);
    this->board.renderBoard(*this->window);
    this->window->display();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }
        else if (this->event.type == sf::Event::MouseButtonPressed && !sent)
        {
            this->handleTurns();
            if (board.isWinner())
            {
                endgame = true;
            }
        }
    }
}

void Game::loadTexture()
{
    this->textures["BOARD"] = new sf::Texture;
    if (!this->textures["BOARD"]->loadFromFile("./asserts/ttc_board.png"))
    {
        throw std::invalid_argument("couldnt load board\n");
    }
}

void Game::run()
{

    while (this->isOpen() && !this->endgame)
    {
        this->update();
        this->render();
    }
}

void Game::handleTurns()
{
    auto mouseData = sf::Mouse::getPosition(*this->window);
    int row = Board::clickToPos(mouseData.x);
    int column = Board::clickToPos(mouseData.y);
    if (board.isEmpty(row, column))
    {
        this->board.setPiece(row, column, this->player);
        this->moved = true;
        this->lastPos.first = row;
        this->lastPos.second = column;
    }
}