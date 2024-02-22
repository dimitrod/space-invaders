#pragma once
#include <raylib.h>

class UI 
{
    public:
        UI();
        ~UI();
        void DrawBaseUI(int screenWidth, int screenHeight, int offset, int score, int highscore);
        void DrawPause();
        void DrawGameOver(int score, int highscore);
        void DrawStart();
        void DrawLevel(int level);

    private:
        Font font;
        Color darkgrey;
        Color yellow;
    
};