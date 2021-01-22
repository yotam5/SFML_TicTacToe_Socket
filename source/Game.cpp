
#pragma once

#include "../header/Game.h"
#include <iostream>

Game::Game()
{
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
    //this->netHandle.init();
    this->lastPos = std::make_pair(0, 0);
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
            std::cout << "send move\n";
            this->netHandle.sendMsg(std::make_pair(2,
                                                   2)); //FIXME -idk why by it goes crash lastpos
            this->sent = true;
            this->moved = false;
            std::cout << "test" << std::endl;
        }
    }
    else if (!this->moved)
    {
        //std::cout << "wating" << std::endl;
        if (this->netHandle.getFullyRecive())
        {
            std::cout << "get message: " << std::endl;
            netHandle.setFullyRecive(false);
            this->sent = false;
        }
    }
    else
    {
        std::cout << "ERROR" << std::endl;
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
        else if (this->event.type == sf::Event::MouseButtonPressed)
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
        this->board.setPiece(row, column, Players::CAPITAL_O);
        //this->lastPos = std::make_pair(row, column);
        this->moved = true;
    }
}