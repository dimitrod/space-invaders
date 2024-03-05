#pragma once
#include <raylib.h>
#include <vector>

class Laser
{
    public:
        Laser(Vector2 position, int speed);
        void Draw();
        void Update();
        bool active = true;
        Rectangle GetRect();
        static void DeleteInactiveLasers(std::vector<Laser>& lasers);

    private:
        Vector2 position;
        int speed;
};