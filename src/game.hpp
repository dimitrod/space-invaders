#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "alienhandler.hpp"
#include "mysteryship.hpp"
#include "shieldboss.hpp"
#include "teleportboss.hpp"
#include "ui.hpp"
#include "highscore.hpp"

class Game 
{
    public:
        Game();
        ~Game();

        void Draw();
        void Update();
        void GameOver();
        void Reset();
        void NextLevel();

        bool info = false; 
        bool pauseMusic = false;

        int gameState = 0;
        int activeGameState = 0;
        int level;

        Music music;
        Music bossMusic;
        Spaceship spaceship;

    private:
        int lives;
        int score;
        int highscore = 0;
        int offset = 50;
        int screenWidth = 750;
        int screenHeight = 700;
        
        float difficulty;

        UI ui;  
        Sound explosionSound;
        std::vector<Obstacle> obstacles;
        AlienHandler alienHandler;  
        MysteryShip mysteryShip;
        Shieldboss shieldboss;
        Teleportboss teleportboss;
        std::vector<Alien> aliens;

        void CheckCollisions();
        void DeleteInactiveLasers(std::vector<Laser>& lasers);   
        void UpdateNormalLevel();
        void UpdateTeleportbossLevel();
        void UpdateShieldbossLevel();
        
};