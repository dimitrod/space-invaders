#include "ui.hpp"
#include "game.hpp"
#include <cstring>
#include <string>

UI::UI()
{
    font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    
}

UI::~UI()
{
    UnloadFont(font);
}

void UI::CenterText(const char *text, int fontSize, int y, Color color)
{
    Vector2 textSize = MeasureTextEx(font, text, fontSize, 2);
    DrawTextEx(font, text, {400 - textSize.x/2, y - textSize.y/2}, fontSize, 2, color);
}

void UI::DrawLives(int lives, Texture2D livesImage)
{
    for (int i = 0; i < lives; i++)
    {    
        DrawTextureV(livesImage, {(float) 75 + 50 * i, 745}, WHITE);
    }
}

void UI::DrawStart(bool info)
{
    CenterText("SPACE INVADERS", 96, 280, RED);
    CenterText("PRESS ENTER TO START", 48, 350, yellow);

    if (info)
    {
        CenterText("PRESS 1 TO SKIP TO FIRST BOSS", 32, 440, yellow);
        CenterText("ARROW KEYS - MOVE LEFT/RIGHT", 32, 480, yellow);    
        CenterText("P - PAUSE/UNPAUSE MUSIC", 32, 520, yellow);
        CenterText("ENTER - PAUSE/UNPAUSE", 32, 560, yellow);
        CenterText("SPACE - SHOOT", 32, 600, yellow);
        CenterText("ESC - QUIT", 32, 640, yellow);
    }
    else
    {
        CenterText("PRESS i TO SHOW/HIDE INFO", 32, 440, GREEN);
    }

    DrawTextEx(font, "START", {570, 740}, 34, 2, yellow);    
  
}

void UI::DrawLevel(int level)
{
    std::string levelNumber = "LEVEL " + std::to_string(level);
    const char * c = levelNumber.c_str();
    DrawTextEx(font, c, {570, 740}, 34, 2, yellow);
}

void UI::DrawBoss()
{
    DrawTextEx(font, "BOSS", {570, 740}, 34, 2, yellow);    
}


std::string FormatWithLeadingZeros(int number, int width) 
{
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

void UI::DrawPause()
{
    CenterText("PAUSE", 64, 350, yellow);
    DrawTextEx(font, "PAUSE", {570, 740}, 34, 2, yellow);   

}

void UI::DrawGameOver(int score, int highscore) 
{

    char scoreTitle[11] = "SCORE ";
    std::string scoreText = FormatWithLeadingZeros(score, 10);
    strcat(scoreTitle, scoreText.c_str());

    CenterText("GAME OVER", 96, 300, RED);
    CenterText("PRESS ENTER TO RESTART", 48, 360, yellow);
    CenterText(scoreTitle, 64, 450, GREEN);
    DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);   


}


void UI::DrawBaseUI(int screenWidth, int screenHeight, int offset, int score, int highscore) 
{
    ClearBackground(darkgrey); 
    DrawRectangleRoundedLines({10, 10, float(screenWidth + offset - 20), float(screenHeight + 2 * offset - 20)}, 0.18f, 20, 2, yellow);
    DrawLineEx({25, 730}, {775, 730}, 3, yellow);

    DrawTextEx(font, "SCORE", {75, 15}, 34, 2, yellow); 
    std::string scoreText = FormatWithLeadingZeros(score, 10);
    DrawTextEx(font, scoreText.c_str(), {75, 40}, 34, 2, yellow); 

    DrawTextEx(font, "HIGHSCORE", {565, 15}, 34, 2, yellow); 
    std::string highscoreText = FormatWithLeadingZeros(highscore, 10);
    DrawTextEx(font, highscoreText.c_str(), {550, 40}, 34, 2, yellow); 

}
