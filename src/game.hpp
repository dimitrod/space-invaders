#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
#include "shieldboss.hpp"
#include "teleportboss.hpp"
#include "ui.hpp"

class Game 
{
    public:
        Game();
        ~Game();

        void Draw();
        void Update();
        void HandleInput();

        bool info = false; 

        int gameState = 0;
        int lives = 0;
        int score = 0;
        int highscore = 0;
        int level = 0;
        int offset = 50;
        int screenWidth = 750;
        int screenHeight = 700;

        Music music;
        Music bossMusic;
        UI ui;

    private:
        void DeleteInactiveLasers(std::vector<Laser> lasers);
        std::vector<Obstacle> CreateObstacles();
        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;

        void UpdateNormalLevel();
        void UpdateTeleportbossLevel();
        void UpdateShieldbossLevel();

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

        Teleportboss teleportboss;

        int activeGameState;
        bool pause = false;
        float difficulty;

        void SaveHighscoreToFile(int highscore);
        int LoadHighscoreFromFile();
        Sound explosionSound;

};