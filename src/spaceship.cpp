#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("img/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    lastLaserTime = 0.0;
}

Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

void Spaceship::Draw()
{
    DrawTexture(image, position.x, position.y, WHITE);
}

void Spaceship::MoveLeft()
{
    position.x -= 7;

    if (position.x < 25)
    {
       position.x = 25;
    } 

}

void Spaceship::MoveRight()
{
    position.x += 7;

    if (position.x > GetScreenWidth() - image.width - 25)
    {
        position.x = GetScreenWidth() - image.width - 25;
    }

}

void Spaceship::FireLaser()
{
    if (GetTime() - lastLaserTime >= 0.35)
    {
        lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, -6));
        lastLaserTime = GetTime();
    }
    
    
}

Rectangle Spaceship::GetRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    lasers.clear();
}