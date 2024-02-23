#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"

class Teleportboss
{
    public:
        Teleportboss();
        ~Teleportboss();
        void createArmor();
        void Reset();
        Vector2 position;
        Vector2 oldPosition;
        void Draw();
        void Update(Vector2 positionNew);
        Rectangle GetRect();
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid;
        bool alive;
    private:

};