#include "laser.hpp"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
    this -> position = position;
    this -> speed = speed;
    this -> active = true;
}

void Laser::Draw()
{
    if(active)
    {
         DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
    }
   
}

void Laser::Update()
{
    
    if(active) 
    {
        position.y += speed;

        if(position.y > GetScreenHeight() - 100 || position.y < 25)
        {
            active = false;
        }
    }
}

Rectangle Laser::GetRect()
{
    Rectangle rect = {position.x, position.y, 4, 15};
    return rect;
}

void Laser::DeleteInactiveLasers(std::vector<Laser>& lasers)
{
    for(auto it = lasers.begin(); it != lasers.end();)
    {
        if (!it -> active)
        {
            it = lasers.erase(it);
        }
        else
        {
            it++;
        }
    }

}