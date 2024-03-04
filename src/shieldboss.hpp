#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"
#include "laser.hpp"

class Shieldboss
{
    public:
        void createArmor();
        void Reset();
        Vector2 position = {465, 150};
        void Draw();
        void Update(int direction);
        Rectangle GetRect();
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid;
        bool alive = false;
        void ShootShieldbossLaser();
        std::vector<Laser> shieldbossLasers;
        void MoveShieldboss();
        void MoveShieldbossDown(int distance);
    private:
        float timeShieldbossFired = 0;
        float shieldbossLaserShootInterval = 0.5;
        int shieldbossDirection = 2;
};