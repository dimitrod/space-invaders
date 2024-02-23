#include "teleportboss.hpp"
#include <raylib.h>


Teleportboss::Teleportboss()
{
    position = {454, 150};
    alive = false;

    

}

Teleportboss::~Teleportboss()
{

}

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

