#include "game.hpp"
#include <iostream>

Game::Game()
{

}

Game::~Game()
{

}

void Game::Draw()
{
    spaceship.Draw();

    for (auto &laser : spaceship.lasers)
    {
        laser.Draw();
    }

    DeleteInactiveLasers();

}

void Game::Update()
{
    for (auto &laser : spaceship.lasers)
    {
        laser.Update();
    }

}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        spaceship.FireLaser();
    }
}

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it -> active)
        {
            it = spaceship.lasers.erase(it);
        }
        else
        {
            it++;
        }
    }
}
