#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
#include "shieldboss.hpp"
#include "teleportboss.hpp"

class Game 
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        int gameState;
        int lives;
        Texture2D livesImage;
        int score;
        int highscore;
        Music music;
        int level;

    private:
        void DeleteInactiveLasers();
        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> CreateAliens();
        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        void MoveAliens();
        void MoveDownAliens(int distance);
        void ShootAlienLaser();
        std::vector<Laser> alienLasers;
        int aliensDirection;
        constexpr static float alienLaserShootInterval = 0.35;
        float timeLastAlienFired;
        MysteryShip mysteryShip;
        float mysteryShipSpawnInterval;
        float timeLastMysteryShipSpawned;
        void CheckCollisions();
        void GameOver();
        void Reset();
        void InitGame();
        void NextLevel();
        void CheckHighscore();

        Shieldboss shieldboss;
        std::vector<Laser> shieldbossLasers;
        void ShootShieldbossLaser();
        void MoveShieldboss();
        void MoveShieldbossDown(int distance);
        int shieldbossDirection;
        float timeShieldbossFired;
        float shieldbossLaserShootInterval;

        Teleportboss teleportboss;
        std::vector<Laser> teleportbossLasers;
        void ShootTeleportbossLaser();
        void MoveTeleportboss();
        int teleportbossDirection;
        float timeTeleportbossFired;
        float teleportbossLaserShootInterval;
        float teleportbossTeleportInterval;
        float teleportbossTeleported;
        int teleportbossLaserDirection;

        int activeGameState;
        bool pause;

        void SaveHighscoreToFile(int highscore);
        int LoadHighscoreFromFile();
        Sound explosionSound;

};