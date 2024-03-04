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
        void Draw();
        void Update(Vector2 positionNew);
        void ShootTeleportbossLaser();
        void MoveTeleportboss();
        Rectangle GetRect();

        Vector2 position = {454, 150};
        Vector2 oldPosition;
        std::vector<Block> blocks;
        std::vector<Laser> teleportbossLasers;
        static std::vector<std::vector<int>> grid;

        bool alive = false;
    
    private:
        int teleportbossLaserDirection = 1;             
        int teleportbossDirection = 2;

        float timeTeleportbossFired = 0;
        float teleportbossLaserShootInterval = 5.0;
        float teleportbossTeleportInterval = 3.0;
        float teleportbossTeleported = 0;

};