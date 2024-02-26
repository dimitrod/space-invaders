#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"

class Shieldboss
{
    public:
        void createArmor();
        void Reset();
        Vector2 position = {465, 150};
        void Draw();
        void Update(int direction);
        Rectangle GetRect();
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid;
        bool alive = false;
    private:

};