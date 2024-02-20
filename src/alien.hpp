#pragma once
#include <raylib.h>

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
        void Update(int direction);
        int GetType();
    private:

};