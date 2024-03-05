#pragma once
#include "alien.hpp"
#include "laser.hpp"

class AlienHandler 
{
    public:
        AlienHandler();
        ~AlienHandler();

        std::vector<Alien> CreateAliens();
        void MoveAliens(std::vector<Alien>& aliens, float difficulty);    
        void ShootAlienLaser(std::vector<Alien>& aliens, float difficulty);
        
        std::vector<Laser> alienLasers;  

    private:
        int aliensDirection = 1;
        constexpr static float alienLaserShootInterval = 0.35;
        float timeLastAlienFired = 0;
        

};