#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

class Game 
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        Texture2D livesImage;
        int score;
        int highscore;
        Music music;

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
        void CheckHighscore();

        void SaveHighscoreToFile(int highscore);
        int LoadHighscoreFromFile();
        Sound explosionSound;

};