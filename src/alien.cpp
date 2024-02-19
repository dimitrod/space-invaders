#include "alien.hpp"

Alien::Alien(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;

    switch (type)
    {
    case 1:
        image = LoadTexture("img/alien_1.png");
        break;
    case 2:
        image = LoadTexture("img/alien_2.png");
        break;
    case 3:
        image = LoadTexture("img/alien_3.png");
        break;
    default:
        image = LoadTexture("img/alien_1.png");
        break;
    }

}

Alien::~Alien()
{

}

void Alien::Draw()
{
    DrawTexture(image, position.x, position.y, WHITE);
}

void Alien::Update()
{

}

int Alien::GetType()
{
    return type;
}

