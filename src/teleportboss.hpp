#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"
#include "laser.hpp"

class Teleportboss
{
    public:
        void createArmor();
        void Reset();
        Vector2 position = {454, 150};
        Vector2 oldPosition;
        void Draw();
        void Update(Vector2 positionNew);
        Rectangle GetRect();
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid;
        bool alive = false;
        void ShootTeleportbossLaser();
        void MoveTeleportboss();
        std::vector<Laser> teleportbossLasers;
    private:
        float timeTeleportbossFired = 0;
        float teleportbossLaserShootInterval = 5.0;
        int teleportbossLaserDirection = 1;             
        int teleportbossDirection = 2;
        float teleportbossTeleportInterval = 3.0;
        float teleportbossTeleported = 0;

};