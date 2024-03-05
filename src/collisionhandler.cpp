#include "collisionhandler.hpp"

void CollisionHandler::ObstacleCollision(std::vector<Block>& blocks, Laser& laser)
{
    auto tl = blocks.begin();

    while (tl != blocks.end()){ 
        if (CheckCollisionRecs(tl -> GetRect(), laser.GetRect()))
        {
            tl = blocks.erase(tl);
            laser.active = false;
        }
        else
        {
            tl++;
        }

    }
}

void CollisionHandler::LaserCollision(Spaceship& spaceship, std::vector<Laser>& lasers, std::vector<Obstacle>& obstacles, int& lives)
{

    for(auto& laser : lasers)
    {
        if (CheckCollisionRecs(spaceship.GetRect(), laser.GetRect()))
        {
            lives--;
            laser.active = false;

        }

        for(auto& obstacle : obstacles)
        {
            CollisionHandler::ObstacleCollision(obstacle.blocks, laser);
         
        }
    }
}

void CollisionHandler::NPCObstacleCollision(std::vector<Obstacle>& obstacles, int& lives, Rectangle rect)
{
    for(auto& obstacle : obstacles)
        {

            auto it = obstacle.blocks.begin();

            while (it != obstacle.blocks.end()){ 
                if (CheckCollisionRecs(it -> GetRect(), rect))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    it++;
                }

            }
        }

}

void CollisionHandler::NPCShipCollision(Spaceship& spaceship, int& lives, Rectangle rect)
{
    if(CheckCollisionRecs(rect, spaceship.GetRect()))
    {
        lives = 0;
    }

}


        
void CollisionHandler::PlayerHit(Laser& laser, int& lives, int& score, int& highscore, Shieldboss& boss, Sound& explosionSound)
{
    if (CheckCollisionRecs(boss.GetRect(), laser.GetRect()) && boss.alive)
    {
        PlaySound(explosionSound);
        score += 15000;
        lives++;
        boss.alive = false;
        laser.active = false;
        Highscore::CheckHighscore(score, highscore);
    }
}

void CollisionHandler::PlayerHit(Laser& laser, int& lives, int& score, int& highscore, Teleportboss& boss, Sound& explosionSound)
{
    if (CheckCollisionRecs(boss.GetRect(), laser.GetRect()) && boss.alive)
    {
        PlaySound(explosionSound);
        score += 25000;
        lives += 2;
        boss.alive = false;
        laser.active = false;
        Highscore::CheckHighscore(score, highscore);
    }
}

void CollisionHandler::PlayerHit(Laser& laser, int& score, int& highscore, MysteryShip& ship, Sound& explosionSound)
{
    if (CheckCollisionRecs(ship.GetRect(), laser.GetRect()) && ship.alive)
    {
        PlaySound(explosionSound);
        score += 500;
        ship.alive = false;
        laser.active = false;
        Highscore::CheckHighscore(score, highscore);
    }
}


void CollisionHandler::PlayerHit(Laser& laser, int& score, int& highscore, std::vector<Alien>& aliens, Sound& explosionSound)
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
            Highscore::CheckHighscore(score, highscore);
        }
        else
        {
            it++;
        }
    }
}