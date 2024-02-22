#pragma once
#include <raylib.h>
#include <vector>
#include "block.hpp"

class Shieldboss
{
    public:
        Shieldboss();
        ~Shieldboss();
        void createArmor();
        void Reset();
        Vector2 position;
        void Draw();
        void Update(int direction);
        Rectangle GetRect();
        std::vector<Block> blocks;
        static std::vector<std::vector<int>> grid;
        bool alive;
    private:

};