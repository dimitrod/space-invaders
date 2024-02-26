#include "block.hpp"

void Block::Draw()
{
    DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255});
}

Rectangle Block::GetRect()
{
    Rectangle rect = {position.x, position.y, 3, 3};
    return rect;
}

