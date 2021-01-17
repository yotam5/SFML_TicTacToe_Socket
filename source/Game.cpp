
#pragma once

#include "../header/Game.h"

Game::Game()
{
    this->loadTexture();
    this->initVariables();
    this->initWindow();
}

Game::~Game()
{
    delete this->window;
}

void Game::initVariables()
{
    this->background.setTexture(*this->textures["BOARD"]);
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
}

void Game::render()
{
    this->window->clear();
    this->window->draw(this->background);
    this->window->display();
}

void Game::pollEvents()
{
    while (this->window->pollEvent(this->event))
    {
        sf::Event::EventType type = this->event.type;
        if (type == sf::Event::Closed)
        {
            this->window->close();
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
    while (this->isOpen())
    {
        this->update();
        this->render();
    }
}