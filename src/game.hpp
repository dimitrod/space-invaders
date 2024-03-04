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

    private:
        bool info = false; 
        bool pauseMusic = false;

        int gameState = 0;
        int lives = 0;
        int score = 0;
        int highscore = 0;
        int level = 0;
        int offset = 50;
        int screenWidth = 750;
        int screenHeight = 700;
        int activeGameState = 0;
        
        float difficulty = 1.0;

        UI ui;  
        Music music;
        Music bossMusic;
        Sound explosionSound;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        Spaceship spaceship;
        MysteryShip mysteryShip;
        Shieldboss shieldboss;
        Teleportboss teleportboss;

        void CheckCollisions();
        void GameOver();
        void Reset();
        void NextLevel();
        std::vector<Laser> DeleteInactiveLasers(std::vector<Laser> lasers);   
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

        
        float mysteryShipSpawnInterval;
        float timeLastMysteryShipSpawned;
        
        void CheckHighscore();
        void SaveHighscoreToFile(int highscore);
        int LoadHighscoreFromFile();
};