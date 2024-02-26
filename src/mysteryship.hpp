#pragma once
#include <raylib.h>

class MysteryShip
{
    public:
        MysteryShip();
        ~MysteryShip();   
        void Draw();
        void Update();
        void Spawn();
        bool alive = false;
        Rectangle GetRect();
    private:
        Vector2 position = {0, 0};
        Texture2D image;
        int speed = 0;
        

};