#pragma once
#include <raylib.h>

class Laser
{
    public:
        Laser(Vector2 position, int speed);
        void Draw();
        void Update();
        bool active = true;
        Rectangle GetRect();

    private:
        Vector2 position;
        int speed;
};