#pragma once
#include <vector>
#include "block.hpp"
#include "laser.hpp"
#include "obstacle.hpp"
#include "spaceship.hpp"
#include "highscore.hpp"
#include "shieldboss.hpp"
#include "teleportboss.hpp"
#include "mysteryship.hpp"
#include "alien.hpp"


class CollisionHandler {
    public:
        static void ObstacleCollision(std::vector<Block>& blocks, Laser& laser);
        static void LaserCollision(Spaceship& spaceship, std::vector<Laser>& lasers, std::vector<Obstacle>& obstacles, int& lives);
        static void NPCObstacleCollision(std::vector<Obstacle>& obstacles, int& lives, Rectangle rect);
        static void NPCShipCollision(Spaceship& spaceship, int& lives, Rectangle rect);
        static void PlayerHit(Laser& laser, int& lives, int& score, int& highscore, Shieldboss& boss, Sound& explosionSound);
        static void PlayerHit(Laser& laser, int& lives, int& score, int& highscore, Teleportboss& boss, Sound& explosionSound);
        static void PlayerHit(Laser& laser, int& score, int& highscore, MysteryShip& ship, Sound& explosionSound);
        static void PlayerHit(Laser& laser, int& score, int& highscore, std::vector<Alien>& aliens, Sound& explosionSound);
    private:

};