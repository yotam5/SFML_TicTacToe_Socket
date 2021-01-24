
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
    this->winner = false;
    this->sent = false;
    this->background.setTexture(*this->textures["BOARD"]);
    this->endgame = false;
    this->lastPos = std::make_pair(1, 1);
    this->moved = false;
    this->moveCounter = 0;
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

bool Game::isTie()
{
    if (this->moveCounter == 9)
    {
        if (!this->board.isWinner())
        {
            return true;
        }
    }
    return false;
}

void Game::update()
{
    this->pollEvents();
    if (this->moved)
    {
        this->moveCounter++;
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
            this->moveCounter++;
            auto msgCopy = this->netHandle.getMsgCopy();
            auto strtest = this->netHandle.convertTo<std::pair<int, int>>(msgCopy);
            this->board.setPiece(strtest.first, strtest.second,
                                 (this->player == Players::CAPITAL_O) ? Players::CAPITAL_X : Players::CAPITAL_O);
            netHandle.setFullyRecive(false);
            this->sent = false;
            if (board.isWinner())
            {
                this->winner = true;
                endgame = true;
            }
        }
    }
    if (this->moveCounter == 9)
    {
        this->endgame = true;
    }
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
                this->winner = true;
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
    this->textures["TIE"] = new sf::Texture;
    if (!this->textures["TIE"]->loadFromFile("./asserts/tie.png"))
    {
        throw std::invalid_argument("couldnt load tie\n");
    }
}

void Game::run()
{
    while (this->isOpen() && !this->endgame)
    {
        this->update();
        this->render();
    }
    std::cin.get(); //wait for key press
    std::cin.get();
}

void Game::render()
{
    this->window->clear();
    this->window->draw(this->background);
    this->board.renderBoard(*this->window);

    if (this->endgame && this->winner)
    {
        this->drawRectLine();
    }
    else if (this->endgame && !this->winner)
    {
        sf::Sprite tmpTie;
        tmpTie.setTexture(*this->textures["TIE"]);
        tmpTie.setOrigin(WIDTH / 4, HEIGHT / 2);
        this->window->draw(tmpTie);
    }
    this->window->display();
}

void Game::drawRectLine()
{
    sf::RectangleShape rect(sf::Vector2f(IMG_SIZE, IMG_SIZE));
    rect.setFillColor(sf::Color(46, 139, 87, 60));
    auto winnerPoses = this->board.getWinnerPoses();
    for (auto pos : winnerPoses)
    {
        float x = pos.second * REPOSITION;
        float y = pos.first * REPOSITION;
        rect.setPosition(sf::Vector2f(y, x));
        this->window->draw(rect);
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
