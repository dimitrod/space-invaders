#include "game.hpp"

Game::Game()
{
    music = LoadMusicStream("sound/music.ogg");
    bossMusic = LoadMusicStream("sound/boss.ogg");
    explosionSound = LoadSound("sound/explosion.ogg");
    highscore = Highscore::LoadHighscoreFromFile();

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

    mysteryShip.Update();

    alienHandler.MoveAliens(aliens, difficulty);
    alienHandler.ShootAlienLaser(aliens, difficulty);

    for (auto &laser : alienHandler.alienLasers)
    {
        laser.Update();
    }
    
    CheckCollisions();

    Laser::DeleteInactiveLasers(alienHandler.alienLasers);
    Laser::DeleteInactiveLasers(spaceship.lasers);

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

    Laser::DeleteInactiveLasers(shieldboss.shieldbossLasers);
    Laser::DeleteInactiveLasers(spaceship.lasers);

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

    Laser::DeleteInactiveLasers(teleportboss.teleportbossLasers);
    Laser::DeleteInactiveLasers(spaceship.lasers);

    if(!teleportboss.alive)
    {
        Reset();
        NextLevel();
    }
}

void Game::GameOver()
{
    gameState = 2;

}

void Game::Init()
{
    level = 0;
    lives = 3; 
    score = 0;
    difficulty = 1.0;
}

void Game::Reset()
{
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

void Game::CheckCollisions()
{
    //Spaceship Laser
    for (auto &laser : spaceship.lasers)
    {
        for(auto& obstacle : obstacles)
        {
            CollisionHandler::ObstacleCollision(obstacle.blocks, laser);
        }

        CollisionHandler::ObstacleCollision(shieldboss.blocks, laser);
        CollisionHandler::ObstacleCollision(teleportboss.blocks, laser);

        CollisionHandler::PlayerHit(laser, score, highscore, aliens, explosionSound);
        CollisionHandler::PlayerHit(laser, lives, score, highscore, shieldboss, explosionSound);
        CollisionHandler::PlayerHit(laser, lives, score, highscore, teleportboss, explosionSound);
        CollisionHandler::PlayerHit(laser, score, highscore, mysteryShip, explosionSound);
        
    }

    CollisionHandler::LaserCollision(spaceship, shieldboss.shieldbossLasers, obstacles, lives);
    CollisionHandler::LaserCollision(spaceship, teleportboss.teleportbossLasers, obstacles, lives);
    CollisionHandler::LaserCollision(spaceship, alienHandler.alienLasers, obstacles, lives);

    for(auto& alien : aliens)
    {
        CollisionHandler::NPCObstacleCollision(obstacles, lives, alien.GetRect());
        CollisionHandler::NPCShipCollision(spaceship, lives, alien.GetRect());
    }

    if(shieldboss.alive)
    {
        CollisionHandler::NPCObstacleCollision(obstacles, lives, shieldboss.GetRect());
        CollisionHandler::NPCShipCollision(spaceship, lives, shieldboss.GetRect());
    }

    if (lives <= 0)
    {
        GameOver();
    }

}
