#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    alive = false;
    position = {0, 0};
    speed = 0;
    image = LoadTexture("img/mystery.png");
}

MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

void MysteryShip::Draw()
{
    if (alive) {
        DrawTexture(image, position.x, position.y, WHITE);
    }
    
}

void MysteryShip::Update()
{
    if (alive)
    {
        position.x += speed;

        if (position.x > GetScreenWidth() - image.width || position.x < 0)
        {
            alive = false;
        }
    }
}

void MysteryShip::Spawn()
{
    alive = true;
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if (side == 0)
    {
        position.x = 0;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - image.width;
        speed = -3;
    }    
    
    

}

