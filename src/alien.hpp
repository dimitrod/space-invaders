#pragma once
#include <raylib.h>
#include <vector>

class Alien
{
    public:
        Alien(int type, Vector2 position);
        ~Alien();
        static Texture2D alienImages[3];
        static void UnloadAlienImages();
        int type;
        Vector2 position;
        void Draw();
        void Update(float direction);
        int GetType();
        Rectangle GetRect();
        
    private:

};