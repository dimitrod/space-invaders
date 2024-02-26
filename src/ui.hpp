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
        void DrawBoss();
        void DrawLevel(int level);

    private:
        Font font;
        Color darkgrey = { 29, 29, 27, 255};
        Color yellow = { 243, 216, 63, 255};
    
};