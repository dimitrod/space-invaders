#include "game.hpp"
#include <iostream>
#include <fstream>
#include <iostream>

Game::Game()
{
    music = LoadMusicStream("sound/music.ogg");
    bossMusic = LoadMusicStream("sound/boss.ogg");
    explosionSound = LoadSound("sound/explosion.ogg");
    highscore = LoadHighscoreFromFile();

    PlayMusicStream(music);
    SetMusicVolume(music, 0.3);
    PlayMusicStream(bossMusic);
    SetMusicVolume(bossMusic, 0.2);
  
}

Game::~Game()
{
    Alien::UnloadAlienImages();
    UnloadMusicStream(music);
    UnloadMusicStream(bossMusic);
    UnloadSound(explosionSound);
}

void Game::Draw()
{
    ui.DrawBaseUI(screenWidth, screenHeight, offset, score, highscore);
    ui.DrawLives(lives, spaceship.image);

    if (gameState != 0)
    {
        spaceship.Draw();
    }

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

    for (auto &laser : alienHandler.alienLasers)
    {
        laser.Draw();
    }

    for (auto &laser : shieldboss.shieldbossLasers)
    {
        laser.Draw();
    }

    for (auto &laser : teleportboss.teleportbossLasers)
    {
        laser.Draw();
    }

    mysteryShip.Draw();
    shieldboss.Draw();
    teleportboss.Draw();

    switch(gameState) {
    case 0:
        ui.DrawStart(info); 
        break;
    case 1:
        ui.DrawLevel(level);
        break;
    case 2:
        ui.DrawGameOver(score, highscore);
        break;
    case 3:
        ui.DrawPause();
        break;
    case 4:
        ui.DrawBoss();
        break;
    case 5:
        ui.DrawBoss();
        break;
    }
}



void Game::Update()

{
    switch(gameState) {
    case 1:
        UpdateNormalLevel();
        break;
    case 4:
        UpdateShieldbossLevel();
        break;
    case 5:
        UpdateTeleportbossLevel();
        break;
    }
}




void Game::UpdateNormalLevel()
{
    
    activeGameState = 1;

    UpdateMusicStream(music);



    for (auto &laser : spaceship.lasers)
    {
        laser.Update();
    }

    alienHandler.MoveAliens(aliens, difficulty);

    mysteryShip.Update();

    alienHandler.ShootAlienLaser(aliens, difficulty);

    for (auto &laser : alienHandler.alienLasers)
    {
        laser.Update();
    }
    
    CheckCollisions();

    DeleteInactiveLasers(alienHandler.alienLasers);
    DeleteInactiveLasers(spaceship.lasers);

    if(aliens.empty())
    {
        Reset();
        NextLevel();
    }

}

void Game::UpdateShieldbossLevel()
{
    UpdateMusicStream(bossMusic);
    activeGameState = 4;

    for (auto &laser : shieldboss.shieldbossLasers)
    {
        laser.Update();
    }

    for (auto &laser : spaceship.lasers)
    {
        laser.Update();
    }

    shieldboss.ShootShieldbossLaser();

    shieldboss.MoveShieldboss();
    
    CheckCollisions();

    DeleteInactiveLasers(shieldboss.shieldbossLasers);
    DeleteInactiveLasers(spaceship.lasers);

    
    if(!shieldboss.alive)
    {
        Reset();
        NextLevel();
    }
}

void Game::UpdateTeleportbossLevel()
{
    UpdateMusicStream(bossMusic);
    activeGameState = 5;

    for (auto &laser : teleportboss.teleportbossLasers)
    {
        laser.Update();
    }

    for (auto &laser : spaceship.lasers)
    {
        laser.Update();
    }

    teleportboss.ShootTeleportbossLaser();

    teleportboss.MoveTeleportboss();
    
    CheckCollisions();

    DeleteInactiveLasers(teleportboss.teleportbossLasers);
    DeleteInactiveLasers(spaceship.lasers);

    if(!teleportboss.alive)
    {
        Reset();
        NextLevel();
    }
}


void Game::DeleteInactiveLasers(std::vector<Laser>& lasers)
{
    for(auto it = lasers.begin(); it != lasers.end();)
    {
        if (!it -> active)
        {
            it = lasers.erase(it);
        }
        else
        {
            it++;
        }
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
    for(auto& laser : shieldboss.shieldbossLasers)
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
    for(auto& laser : teleportboss.teleportbossLasers)
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


    for(auto& laser : alienHandler.alienLasers)
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

    //Shieldboss and Obstacle

    if(shieldboss.alive)
    {
        for(auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();

            while (it != obstacle.blocks.end()){ 
                if (CheckCollisionRecs(it -> GetRect(), shieldboss.GetRect()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    it++;
                }

            }
        }

        if(CheckCollisionRecs(shieldboss.GetRect(), spaceship.GetRect()))
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
    level = 0;
    lives = 3; 
    score = 0;
    difficulty = 1.0;

    spaceship.Reset();
    aliens.clear();
    alienHandler.alienLasers.clear();
    shieldboss.shieldbossLasers.clear();
    teleportboss.teleportbossLasers.clear();
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
            teleportboss.createArmor();
            gameState = 5;
            obstacles = Obstacle::CreateObstacles();
        }
        else
        {
            shieldboss.alive = true;
            shieldboss.createArmor();
            gameState = 4;
            obstacles = Obstacle::CreateObstacles();
        }

    }
    else 
    {
        aliens = alienHandler.CreateAliens();  
        obstacles = Obstacle::CreateObstacles();
        gameState = 1;
        mysteryShip.timeLastMysteryShipSpawned = GetTime();
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
