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
        void Appear();
        Rectangle GetRect();

        bool alive = false;
        float timeLastMysteryShipSpawned = 0;
 
    private:
        Vector2 position = {0, 0};
        Texture2D image;
        int speed = 0;
        float mysteryShipSpawnInterval = GetRandomValue(10, 20);
        
        

};