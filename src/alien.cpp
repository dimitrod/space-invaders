#include "alien.hpp"

Texture2D Alien::alienImages[3] = {};

Alien::Alien(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;

    if(alienImages[type -1].id == 0)
    {
        alienImages[0] = LoadTexture("img/alien_1.png");
        alienImages[1] = LoadTexture("img/alien_2.png");
        alienImages[2] = LoadTexture("img/alien_3.png");
    }

    switch (type)
    {
    case 1:
        alienImages[0] = LoadTexture("img/alien_1.png");
        break;
    case 2:
        alienImages[1] = LoadTexture("img/alien_2.png");
        break;
    case 3:
        alienImages[2] = LoadTexture("img/alien_3.png");
        break;
    default:
        alienImages[0] = LoadTexture("img/alien_1.png");
        break;
    }

}

Alien::~Alien()
{

}

void Alien::Draw()
{
    DrawTexture(alienImages[type - 1], position.x, position.y, WHITE);
}

int Alien::GetType()
{
    return type;
}

void Alien::UnloadAlienImages()
{
    for (int i = 0; i <= 3; i++)
    {
        UnloadTexture(alienImages[i]);
    }
}

void Alien::Update(int direction)
{
    position.x += direction;
}

Rectangle Alien::GetRect()
{
    return {position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height)};
}