#include "ui.hpp"
#include "game.hpp"
#include <cstring>
#include <string>

UI::UI()
{
    font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    darkgrey = { 29, 29, 27, 255};
    yellow = { 243, 216, 63, 255};
}

UI::~UI()
{
    UnloadFont(font);
}   

void UI::DrawStart()
{
    


    Vector2 titleText = MeasureTextEx(font, "SPACE INVADERS", 96, 2);
    Vector2 enterText = MeasureTextEx(font, "PRESS ENTER TO START", 48, 2);
    Vector2 tutorialText = MeasureTextEx(font, "ARROW KEYS - MOVE LEFT/RIGHT", 32, 2);
    Vector2 tutorialText2 = MeasureTextEx(font, "ENTER - PAUSE/UNPAUSE", 32, 2);
    Vector2 tutorialText3 = MeasureTextEx(font, "SPACE - SHOOT", 32, 2);
    Vector2 tutorialText4 = MeasureTextEx(font, "PRESS 1 IN START - SKIP TO FIRST BOSS", 32, 2);
    Vector2 tutorialText5 = MeasureTextEx(font, "P - PAUSE/UNPAUSE MUSIC", 32, 2);
    DrawTextEx(font, "SPACE INVADERS", {400 - titleText.x/2, 300 - titleText.y/2}, 96, 2, RED); 
    DrawTextEx(font, "PRESS ENTER TO START", {400 - enterText.x/2, 350 - enterText.y/2}, 48, 2, yellow);
    DrawTextEx(font, "PRESS 1 IN START - SKIP TO FIRST BOSS", {400 - tutorialText4.x/2, 460 - tutorialText4.y/2}, 32, 2, yellow); 
    DrawTextEx(font, "ARROW KEYS - MOVE LEFT/RIGHT", {400 - tutorialText.x/2, 500 - tutorialText.y/2}, 32, 2, yellow); 
    DrawTextEx(font, "P - PAUSE/UNPAUSE MUSIC", {400 - tutorialText5.x/2, 540 - tutorialText5.y/2}, 32, 2, yellow); 
    DrawTextEx(font, "ENTER - PAUSE/UNPAUSE", {400 - tutorialText2.x/2, 580 - tutorialText2.y/2}, 32, 2, yellow);
    DrawTextEx(font, "SPACE - SHOOT", {400 - tutorialText3.x/2, 620 - tutorialText3.y/2}, 32, 2, yellow); 
    

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


std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

void UI::DrawPause()
{
    Vector2 pauseText = MeasureTextEx(font, "PAUSE", 64, 2);
    DrawTextEx(font, "PAUSE", {400 - pauseText.x/2, 350 - pauseText.y/2}, 64, 2, yellow);  
    DrawTextEx(font, "PAUSE", {570, 740}, 34, 2, yellow);    
}

void UI::DrawGameOver(int score, int highscore) 
{
    Vector2 gameOverText = MeasureTextEx(font, "GAME OVER", 96, 2);
    Vector2 theRestartText = MeasureTextEx(font, "PRESS ENTER TO RESTART", 48, 2);
    char scoreTitle[11] = "SCORE ";
    std::string scoreText = FormatWithLeadingZeros(score, 10);
    strcat( scoreTitle, scoreText.c_str());
    Vector2 hsText = MeasureTextEx(font, scoreTitle, 64, 2);
    DrawTextEx(font, "GAME OVER", {400 - gameOverText.x/2, 300 - gameOverText.y/2}, 96, 2, RED);  
    DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);   
    DrawTextEx(font, "PRESS ENTER TO RESTART", {132 - theRestartText.x/2, 360 - theRestartText.y/2}, 48, 2, yellow);  
    DrawTextEx(font, scoreTitle, {400 - hsText.x/2, 450 - hsText.y/2}, 64, 2, GREEN); 

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
