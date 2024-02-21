#include <raylib.h>
#include "game.hpp"
#include <cstring>
#include <string>

std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}


int main()
{
    Color darkgrey = { 29, 29, 27, 255};
    Color yellow = { 243, 216, 63, 255};
    int offset = 50;
    const int screenWidth = 750;
    const int screenHeight = 700;
    float shipOffset = 50.0;

    InitWindow(screenWidth + offset, screenHeight + 2 * offset, "SPACE INVADERS");
    SetTargetFPS(60);

    InitAudioDevice();
    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    Game game;

    game.livesImage = LoadTexture("img/spaceship.png");

    while (!WindowShouldClose())
    {
        
        game.HandleInput();
        game.Update();

        BeginDrawing();

        ClearBackground(darkgrey); 
        DrawRectangleRoundedLines({10, 10, float(screenWidth + offset - 20), float(screenHeight + 2 * offset - 20)}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        game.Draw();


        DrawTextEx(font, "SCORE", {75, 15}, 34, 2, yellow); 
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {75, 40}, 34, 2, yellow); 

        DrawTextEx(font, "HIGHSCORE", {565, 15}, 34, 2, yellow); 
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {635, 40}, 34, 2, yellow); 


        
        if (game.gameState == 0)
        {
            Vector2 titleText = MeasureTextEx(font, "SPFAKCE INVADERS", 64, 2);
            Vector2 enterText = MeasureTextEx(font, "PRESS ENTER TO START", 48, 2);
            DrawTextEx(font, "SPFAKCE INVADERS", {400 - titleText.x/2, 350 - titleText.y/2}, 64, 2, yellow);  
            DrawTextEx(font, "TITLE", {570, 740}, 34, 2, yellow);    
            DrawTextEx(font, "PRESS ENTER TO START", {400 - enterText.x/2, 400 - enterText.y/2}, 48, 2, yellow);         
        }
        else if(game.gameState == 1) {
            UpdateMusicStream(game.music);
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } 
        else if (game.gameState == 2)
        {
            Vector2 gameOverText = MeasureTextEx(font, "GAME OVER", 64, 2);
            Vector2 restartText = MeasureTextEx(font, "PRESS ENTER TO START", 48, 2);
            char scoreTitle[11] = "SCORE ";
            strcat( scoreTitle, scoreText.c_str());
            Vector2 hsText = MeasureTextEx(font, scoreTitle, 64, 2);
            DrawTextEx(font, "GAME OVER", {400 - gameOverText.x/2, 350 - gameOverText.y/2}, 64, 2, yellow);  
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);   
            DrawTextEx(font, "PRESS ENTER TO RESTART", {400 - restartText.x/2, 400 - restartText.y/2}, 48, 2, yellow); 
            DrawTextEx(font, scoreTitle, {400 - hsText.x/2, 450 - hsText.y/2}, 64, 2, yellow); 

        }
        else if (game.gameState == 3)
        {
            Vector2 pauseText = MeasureTextEx(font, "PAUSE", 64, 2);
            DrawTextEx(font, "PAUSE", {400 - pauseText.x/2, 350 - pauseText.y/2}, 64, 2, yellow);  
            DrawTextEx(font, "PAUSE", {570, 740}, 34, 2, yellow);           
        }
       
        for (int i = 0; i < game.lives; i++)
        {    
            DrawTextureV(game.livesImage, {shipOffset + 25 + shipOffset * i, 745}, WHITE);
        }




        
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}