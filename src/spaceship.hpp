#pragma once
#include <raylib.h>
#include "laser.hpp"
#include <vector>

class Spaceship 
{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        void Reset();
        std::vector<Laser> lasers;
        Rectangle GetRect();
        Texture2D image;

    private:
        Vector2 position;
        double lastLaserTime;
        Sound laserSound;
};