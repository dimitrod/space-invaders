#include "game.hpp"
#include <iostream>
#include <fstream>

Game::Game()
{
    music = LoadMusicStream("sound/music.ogg");
    explosionSound = LoadSound("sound/explosion.ogg");
    PlayMusicStream(music);
    gameState = 0;
    pause = false;
    livesImage = LoadTexture("img/spaceship.png");
}

Game::~Game()
{
    Alien::UnloadAlienImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
    UnloadTexture(livesImage);
}

void Game::Draw()
{
    spaceship.Draw();

    shieldboss.Draw();

    teleportboss.Draw();

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

    for (auto &laser : shieldbossLasers)
    {
        laser.Draw();
    }

    for (auto &laser : teleportbossLasers)
    {
        laser.Draw();
    }

    mysteryShip.Draw();

}

void Game::Update()
{
    if (gameState == 0)
    {

        if(IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
        if(IsKeyDown(49))
        {
            Reset();
            InitGame();
            Reset();
            level = 2;
            NextLevel();
        }
    }
    else if(gameState == 1) 
    {
        UpdateMusicStream(music);

        double currentTime = GetTime();
        activeGameState = 1;

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

        if(aliens.empty())
        {
            Reset();
            NextLevel();
        }
    }  
    else if (gameState == 2)
    {

        if(IsKeyDown(KEY_ENTER))
        {
            Reset();
            InitGame();
        }
        if(IsKeyDown(49))
        {
            Reset();
            InitGame();
            Reset();
            level = 2;
            NextLevel();
        }
    }
    else if (gameState == 3)
    {

    }
    else if (gameState == 4)
    {
        activeGameState = 4;

        for (auto &laser : shieldbossLasers)
        {
            laser.Update();
        }

        for (auto &laser : spaceship.lasers)
        {
            laser.Update();
        }

        ShootShieldbossLaser();

        MoveShieldboss();
       
        CheckCollisions();

        DeleteInactiveLasers();

        
        if(!shieldboss.alive)
        {
            Reset();
            NextLevel();
        }
        
    }
    else if (gameState == 5)
    {
        activeGameState = 5;

        for (auto &laser : teleportbossLasers)
        {
            laser.Update();
        }

        for (auto &laser : spaceship.lasers)
        {
            laser.Update();
        }

        ShootTeleportbossLaser();

        MoveTeleportboss();
       
        CheckCollisions();

        DeleteInactiveLasers();

        
        if(!teleportboss.alive)
        {
            Reset();
            NextLevel();
        }
        
    }


}

void Game::HandleInput()
{
    
    if (IsKeyPressed(KEY_P))
    {
        pause = !pause;

        if (pause) PauseMusicStream(music);
        else ResumeMusicStream(music);
    }


    if (IsKeyPressed(KEY_ENTER))
    {
        if (gameState == 3)
        {
            gameState = activeGameState;
        }
        else if (gameState == 1 || gameState == 4 || gameState == 5)
        {
            gameState = 3;
        }

    }

    if(gameState == 1 || gameState == 4 || gameState == 5){
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

    for(auto it = shieldbossLasers.begin(); it != shieldbossLasers.end();)
    {
        if (!it -> active)
        {
            it = shieldbossLasers.erase(it);
        }
        else
        {
            it++;
        }
    }

    for(auto it = teleportbossLasers.begin(); it != teleportbossLasers.end();)
    {
        if (!it -> active)
        {
            it = teleportbossLasers.erase(it);
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
        alien.position.y += distance * (difficulty * 1.5);
    }
}


void Game::ShootAlienLaser()
{
    double currentTime = GetTime();

    if (currentTime - timeLastAlienFired >= alienLaserShootInterval - (difficulty-1)/8 && !aliens.empty())
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

    auto bl = shieldboss.blocks.begin();

    while (bl != shieldboss.blocks.end()){ 
        if (CheckCollisionRecs(bl -> GetRect(), laser.GetRect()))
        {
            bl = shieldboss.blocks.erase(bl);
            laser.active = false;
        }
        else
        {
            bl++;
        }

    }

    auto tl = teleportboss.blocks.begin();

    while (tl != teleportboss.blocks.end()){ 
        if (CheckCollisionRecs(tl -> GetRect(), laser.GetRect()))
        {
            tl = teleportboss.blocks.erase(tl);
            laser.active = false;
        }
        else
        {
            tl++;
        }

    }

    if (CheckCollisionRecs(shieldboss.GetRect(), laser.GetRect()) && shieldboss.alive)
    {
        PlaySound(explosionSound);
        score += 15000;
        lives++;
        shieldboss.alive = false;
        laser.active = false;
        CheckHighscore();
    }

    if (CheckCollisionRecs(teleportboss.GetRect(), laser.GetRect()) && teleportboss.alive)
    {
        PlaySound(explosionSound);
        score += 25000;
        lives += 2;
        teleportboss.alive = false;
        laser.active = false;
        CheckHighscore();
    }
        
    }

    //Shieldboss Laser
    for(auto& laser : shieldbossLasers)
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
         auto et = obstacle.blocks.begin();

            while (et != obstacle.blocks.end()){ 
                if (CheckCollisionRecs(et -> GetRect(), laser.GetRect()))
                {
                    et = obstacle.blocks.erase(et);
                    laser.active = false;
                }
                else
                {
                    et++;
                }

            }
        }

    }


   //Teleportboss Laser
    for(auto& laser : teleportbossLasers)
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
         auto et = obstacle.blocks.begin();

            while (et != obstacle.blocks.end()){ 
                if (CheckCollisionRecs(et -> GetRect(), laser.GetRect()))
                {
                    et = obstacle.blocks.erase(et);
                    laser.active = false;
                }
                else
                {
                    et++;
                }

            }
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
    gameState = 2;

}

void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    shieldbossLasers.clear();
    teleportbossLasers.clear();
    obstacles.clear();
    shieldboss.Reset();
    teleportboss.Reset();
}


void Game::NextLevel()
{
    level++;
    if (difficulty < 2.0) difficulty += 0.1;

    if(level % 3 == 0) {
        Reset();
        if(GetRandomValue(0, 1) == 0)
        {
            teleportboss.alive = true;
            teleportbossDirection = 2;
            timeTeleportbossFired = 0;
            teleportbossLaserDirection = 1;
            teleportbossLaserShootInterval = 5.0;
            teleportbossTeleportInterval = 3.0;
            teleportbossTeleported = 0;
            teleportboss.createArmor();
            gameState = 5;
            obstacles = CreateObstacles();
        }
        else
        {
            shieldboss.alive = true;
            shieldbossDirection = 2;
            timeShieldbossFired = 0;
            shieldbossLaserShootInterval = 0.5;
            shieldboss.createArmor();
            gameState = 4;
            obstacles = CreateObstacles();
        }

 
    }
    else 
    {
        obstacles = CreateObstacles();
        aliens = CreateAliens();
        aliensDirection = 1;
        timeLastAlienFired = 0;
        gameState = 1;
        mysteryShipSpawnInterval = GetRandomValue(10, 20);
        timeLastMysteryShipSpawned = GetTime();
    }
    
    
}

void Game::InitGame()
{
    level = 0;
    lives = 3; 
    score = 0;
    difficulty = 2.0;
    highscore = LoadHighscoreFromFile();
    NextLevel();
    
}



void Game::ShootTeleportbossLaser()
{

    if (GetTime() - timeTeleportbossFired >= teleportbossLaserShootInterval && teleportboss.alive)
    {
        

        if (teleportbossLaserDirection == 1)
        {
            float shotStart = GetRandomValue(0, 440);

            for (int i = 0; i < 30; i++)
            {
                
                teleportbossLasers.push_back(Laser({shotStart + i * 12, teleportboss.position.y + i * 2}, 8));
            
            }

           teleportbossLaserDirection = -1;
        }
        else if (teleportbossLaserDirection == -1)
        {
            float shotStart = GetRandomValue(0, 440);

            for (int i = 30; i > 0; i--)
            {
                
                teleportbossLasers.push_back(Laser({shotStart + (30 - i) * 12, teleportboss.position.y + i * 2}, 8));
            
            }
            teleportbossLaserDirection = 1;
        }

        timeTeleportbossFired = GetTime();
    }


}

void Game::MoveTeleportboss()
{
    if (GetTime() - teleportbossTeleported >= teleportbossTeleportInterval && teleportboss.alive)
    {
        teleportboss.Update({(float) GetRandomValue(25, 727), (float) GetRandomValue(100, 400)});
        teleportbossLasers.push_back(Laser({teleportboss.position.x + 23, teleportboss.position.y + 20}, 12));
        teleportbossLasers.push_back(Laser({teleportboss.position.x + 24, teleportboss.position.y + 24}, 12));
        teleportbossLasers.push_back(Laser({teleportboss.position.x + 25, teleportboss.position.y + 24}, 12));
        teleportbossLasers.push_back(Laser({teleportboss.position.x + 26, teleportboss.position.y + 20}, 12));
        teleportbossTeleported = GetTime();
    }

}


void Game::ShootShieldbossLaser()
{

    if (GetTime() - timeShieldbossFired >= shieldbossLaserShootInterval && shieldboss.alive)
    {
        shieldbossLasers.push_back(Laser({shieldboss.position.x + 26, shieldboss.position.y + 49}, 6));
        shieldbossLasers.push_back(Laser({shieldboss.position.x + 46, shieldboss.position.y + 49}, 6));
        timeShieldbossFired = GetTime();
    }

}

void Game::MoveShieldboss()
{
     if(shieldboss.position.x + 69 > GetScreenWidth() - 25)
        {
            shieldbossDirection = GetRandomValue(-4, -1);
            MoveShieldbossDown(12);
        }
        else if (shieldboss.position.x < 25)
        {
            shieldbossDirection = GetRandomValue(1, 4);
            MoveShieldbossDown(12);
        }

        shieldboss.Update(shieldbossDirection);
    
}

void Game::MoveShieldbossDown(int distance)
{
        shieldboss.position.y += distance;
        for (auto& block : shieldboss.blocks)
    {
        block.position.y += distance;
    }
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
