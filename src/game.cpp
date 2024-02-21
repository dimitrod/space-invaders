#include "game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
{
    music = LoadMusicStream("sound/music.ogg");
    explosionSound = LoadSound("sound/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

Game::~Game()
{
    Alien::UnloadAlienImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
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

    for(auto& alien : aliens)
    {
        alien.Draw();
    }

    for (auto &laser : alienLasers)
    {
        laser.Draw();
    }

    mysteryShip.Draw();

}

void Game::Update()
{
    if(run) 
    {
        double currentTime = GetTime();

        if(currentTime - timeLastMysteryShipSpawned > mysteryShipSpawnInterval)
        {
            mysteryShip.Spawn();
            timeLastMysteryShipSpawned = currentTime;
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto &laser : spaceship.lasers)
        {
            laser.Update();
        }

        MoveAliens();

        mysteryShip.Update();

        ShootAlienLaser();

        for (auto &laser : alienLasers)
        {
            laser.Update();
        }
        
        CheckCollisions();

        DeleteInactiveLasers();
    } else {

        DrawText("Game Over", GetScreenWidth() / 2 - MeasureText("Game Over", 40) / 2, GetScreenHeight() / 2 - 40, 40, RED);

        if(IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
    }

}

void Game::HandleInput()
{
    // if (IsKeyPressed(65))
    //    {
    //         run = !run;
    //    }


    if(run){
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

    for(auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it -> active)
        {
            it = alienLasers.erase(it);
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
        obstacles.push_back(Obstacle({offset_x, float (GetScreenHeight() - 200)}));
    }

    return obstacles;
}

std::vector<Alien> Game::CreateAliens()
{
    std::vector<Alien> aliens;
    int alienWidth = 50;
    float gap = (GetScreenWidth() - 11 * alienWidth) / 12;

    for (int row = 0; row < 5; row++)
    {
       for (int col = 0; col < 11; col++)
       {
            int alienType;

            if (row == 0)
            {
                alienType = 3;
            }
            else if (row < 3)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }

            float offset_x = 75 + col * 55;
            float offset_y = 110 + row * 55;

            aliens.push_back(Alien(alienType, {offset_x, offset_y}));
       }
    }

    return aliens;
}

void Game::MoveAliens()
{
    for (auto &alien : aliens)
    {
        if(alien.position.x + alien.alienImages[alien.type -1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;
            MoveDownAliens(4);
        }
        else if (alien.position.x < 25)
        {
            aliensDirection = 1;
            MoveDownAliens(4);
        }

        alien.Update(aliensDirection);

    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto &alien : aliens)
    {
        alien.position.y += distance;
    }
}


void Game::ShootAlienLaser()
{
    double currentTime = GetTime();

    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type -1].width/2, alien.position.y + alien.alienImages[alien.type -1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

void Game::CheckCollisions()
{
    //Spaceship Laser
    for (auto &laser : spaceship.lasers)
    {
        auto it = aliens.begin();

        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it -> GetRect(), laser.GetRect()))
            {
                PlaySound(explosionSound);
                score += 100 * it -> type;
                it = aliens.erase(it);
                laser.active = false;
                CheckHighscore();
            }
            else
            {
                it++;
            }
        }

        for(auto& obstacle : obstacles)
        {
         auto it = obstacle.blocks.begin();

            while (it != obstacle.blocks.end()){ 
                if (CheckCollisionRecs(it -> GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    it++;
                }

        }
    }

    if (CheckCollisionRecs(mysteryShip.GetRect(), laser.GetRect()))
    {
        PlaySound(explosionSound);
        score += 500;
        mysteryShip.alive = false;
        laser.active = false;
        CheckHighscore();
    }

        
    }

    //Alien Lasers

    for(auto& laser : alienLasers)
    {
        if (CheckCollisionRecs(spaceship.GetRect(), laser.GetRect()))
        {
            lives--;
            laser.active = false;

            if (lives == 0)
            {
                GameOver();
            }
        }

        for(auto& obstacle : obstacles)
        {
         auto it = obstacle.blocks.begin();

            while (it != obstacle.blocks.end()){ 
                if (CheckCollisionRecs(it -> GetRect(), laser.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    it++;
                }

            }
        }

    }

    //Alien and Obstacle

    for(auto& alien : aliens)
    {
        for(auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();

            while (it != obstacle.blocks.end()){ 
                if (CheckCollisionRecs(it -> GetRect(), alien.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    it++;
                }

            }
        }

        if(CheckCollisionRecs(alien.GetRect(), spaceship.GetRect()))
        {
            GameOver();
        }

    }


}

void Game::GameOver()
{
    run = false;

}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0;
    lives = 3;
    run = true;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
    timeLastMysteryShipSpawned = 0;
    score = 0;
    highscore = LoadHighscoreFromFile();
}

void Game::CheckHighscore() 
{
    if (score > highscore) 
    {
        highscore = score;
        SaveHighscoreToFile(highscore);
    }

}


void Game::SaveHighscoreToFile(int highscore) 
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open())
    {
        highscoreFile << highscore;
        highscoreFile.close();
    }
    else
    {
        std::cerr << "Failed to save highscore to file!" << std::endl;
    }

}


int Game::LoadHighscoreFromFile()
{
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");

    if(highscoreFile.is_open())
    {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();

    }
    else
    {
        std::cerr << "Failed to load highscore from file!" << std::endl;
    }

    return loadedHighscore;
}
