#include "game.hpp"
#include <iostream>

Game::Game()
{
    obstacles = CreateObstacles();
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

    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
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

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - 4 * obstacleWidth) / 5;

    for (int i = 0; i < 4; i++)
    {
        float offset_x = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offset_x, float (GetScreenHeight() - 100)}));
    }

    return obstacles;
}