#include <raylib.h>
#include "game.hpp"
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

        if(game.run) {
            UpdateMusicStream(game.music);
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } 
        else
        {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);           
        }
       
        for (int i = 0; i < game.lives; i++)
        {
            
            DrawTextureV(game.livesImage, {shipOffset + 25 + shipOffset * i, 745}, WHITE);
        }


        DrawTextEx(font, "SCORE", {75, 15}, 34, 2, yellow); 
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {75, 40}, 34, 2, yellow); 

        DrawTextEx(font, "HIGHSCORE", {565, 15}, 34, 2, yellow); 
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {635, 40}, 34, 2, yellow); 

        game.Draw();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}