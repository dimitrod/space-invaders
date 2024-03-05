#pragma once
#include "alien.hpp"

class AlienHandler 
{
    public:
        AlienHandler();
        ~AlienHandler();

        std::vector<Alien> CreateAliens();
        void MoveAliens(std::vector<Alien>& aliens, float difficulty);

    private:
        int aliensDirection = 1;
        

};