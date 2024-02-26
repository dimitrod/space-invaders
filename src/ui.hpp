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
        void DrawStart(bool info);
        void DrawBoss();
        void DrawLevel(int level);
        void DrawLives(int lives, Texture2D livesImage);
    private:
        Font font;
        Color darkgrey = { 29, 29, 27, 255};
        Color yellow = { 243, 216, 63, 255};
        void CenterText(const char *text, int fontSize, int y, Color color);
};