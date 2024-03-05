#include "alienhandler.hpp"

AlienHandler::AlienHandler() {
    
}

AlienHandler::~AlienHandler() {

}

std::vector<Alien> AlienHandler::CreateAliens() {

    std::vector<Alien> aliens;

    for (int row = 0; row < 5; row++)
    {
       for (int col = 0; col < 11; col++)
       {
            int alienType;

            if (row == 0)
            {
                alienType = 3;
            }
            else if (row < 3)
            {
                alienType = 2;
            }
            else
            {
                alienType = 1;
            }

            float offset_x = 75 + col * 55;
            float offset_y = 110 + row * 55;

            aliens.push_back(Alien(alienType, {offset_x, offset_y}));
       }
    }

    return aliens;
}

void AlienHandler::MoveAliens(std::vector<Alien>& aliens, float difficulty)
{
    for (auto &alien : aliens)
    {
        if(alien.position.x + alien.alienImages[alien.type -1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -1;

            for (auto &alien : aliens)
            {
                alien.position.y += (float) 4 * difficulty;

            }
           
        }
        else if (alien.position.x < 25)
        {
            aliensDirection = 1;

            for (auto &alien : aliens)
            {
                alien.position.y += (float) 4 * difficulty;

            }
        }

        alien.Update(aliensDirection);

    }

}


void AlienHandler::ShootAlienLaser(std::vector<Alien>& aliens, float difficulty)
{
    double currentTime = GetTime();

    if (currentTime - timeLastAlienFired >= alienLaserShootInterval - (difficulty-1)/8 && !aliens.empty())
    {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type -1].width/2, alien.position.y + alien.alienImages[alien.type -1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}


