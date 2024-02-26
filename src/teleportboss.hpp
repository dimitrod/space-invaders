#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"

class Teleportboss
{
    public:
        void createArmor();
        void Reset();
        Vector2 position = {454, 150};
        Vector2 oldPosition;
        void Draw();
        void Update(Vector2 positionNew);
        Rectangle GetRect();
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid;
        bool alive = false;
    private:

};