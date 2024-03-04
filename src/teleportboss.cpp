#include "teleportboss.hpp"
#include <raylib.h>

void Teleportboss::createArmor()
{
   for (unsigned int row = 0; row < grid.size(); row++)
    {
        for (unsigned int col = 0; col < grid[0].size(); col++)
        {
            if (grid[row][col] == 1)
            {
                float pos_x = position.x + col * 3;
                float pos_y = position.y + row * 3;
                Block block = Block({pos_x, pos_y});
                blocks.push_back(block);
            }
        }
    }
}

void Teleportboss::Reset()
{
    alive = false;
    position = {465, 150};
    blocks.clear();
}

void Teleportboss::Draw()
{
    if (alive) {
        DrawRectangle(position.x + 18, position.y + 6, 12, 12, RED);
        
        for (auto& block : blocks)
        {
            block.Draw();
        }
    }
}

void Teleportboss::Update(Vector2 positionNew)
{
    oldPosition = position;
    position = positionNew;

    for (auto& block : blocks)
    {
        block.position.x -= oldPosition.x - positionNew.x;
        block.position.y -= oldPosition.y - positionNew.y;
    }

}

Rectangle Teleportboss::GetRect()
{
    float width = 12;
    float height = 12;
    return {position.x + 18, position.y + 6, width, height};
}


std::vector<std::vector<int>> Teleportboss::grid = {
        {1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1}, 
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1}, 
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1,0, 0, 0, 0}
    };



void Teleportboss::ShootTeleportbossLaser()
{

    if (GetTime() - timeTeleportbossFired >= teleportbossLaserShootInterval && alive)
    {
        

        if (teleportbossLaserDirection == 1)
        {
            float shotStart = GetRandomValue(0, 440);

            for (int i = 0; i < 30; i++)
            {
                
                teleportbossLasers.push_back(Laser({shotStart + i * 12, position.y + i * 2}, 8));
            
            }

           teleportbossLaserDirection = -1;
        }
        else if (teleportbossLaserDirection == -1)
        {
            float shotStart = GetRandomValue(0, 440);

            for (int i = 30; i > 0; i--)
            {
                
                teleportbossLasers.push_back(Laser({shotStart + (30 - i) * 12, position.y + i * 2}, 8));
            
            }
            teleportbossLaserDirection = 1;
        }

        timeTeleportbossFired = GetTime();
    }


}

void Teleportboss::MoveTeleportboss()
{
    if (GetTime() - teleportbossTeleported >= teleportbossTeleportInterval && alive)
    {
        Update({(float) GetRandomValue(25, 727), (float) GetRandomValue(100, 400)});
        teleportbossLasers.push_back(Laser({position.x + 23, position.y + 20}, 12));
        teleportbossLasers.push_back(Laser({position.x + 24, position.y + 24}, 12));
        teleportbossLasers.push_back(Laser({position.x + 25, position.y + 24}, 12));
        teleportbossLasers.push_back(Laser({position.x + 26, position.y + 20}, 12));
        teleportbossTeleported = GetTime();
    }

}
