#include "shieldboss.hpp"
#include <raylib.h>


void Shieldboss::createArmor()
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

void Shieldboss::ShootShieldbossLaser()
{

    if (GetTime() - timeShieldbossFired >= shieldbossLaserShootInterval && alive)
    {
        shieldbossLasers.push_back(Laser({position.x + 26, position.y + 49}, 6));
        shieldbossLasers.push_back(Laser({position.x + 46, position.y + 49}, 6));
        timeShieldbossFired = GetTime();
    }

}

void Shieldboss::Reset()
{
    alive = false;
    position = {465, 150};
    blocks.clear();
}

void Shieldboss::Draw()
{
    if (alive) {
        DrawRectangle(position.x + 26, position.y, 17, 17, RED);
        
        for (auto& block : blocks)
        {
            block.Draw();
        }
    }
}

void Shieldboss::Update(int direction)
{
    position.x += direction;

    for (auto& block : blocks)
    {
        block.position.x += direction;
    }
}

Rectangle Shieldboss::GetRect()
{
    float width = 17;
    float height = 17;
    return {position.x + 26, position.y, width, height};
}


void Shieldboss::MoveShieldboss()
{
     if(position.x + 69 > GetScreenWidth() - 25)
        {
            shieldbossDirection = GetRandomValue(-4, -1);
            MoveShieldbossDown(16);
        }
        else if (position.x < 25)
        {
            shieldbossDirection = GetRandomValue(1, 4);
            MoveShieldbossDown(16);
        }

        Update(shieldbossDirection);
    
}

void Shieldboss::MoveShieldbossDown(int distance)
{
        position.y += distance;
        for (auto& block : blocks)
    {
        block.position.y += distance;
    }
}




std::vector<std::vector<int>> Shieldboss::grid = {
        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0}
    };

