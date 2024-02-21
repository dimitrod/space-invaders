#include <raylib.h>
#include "game.hpp"


int main()
{
    Color darkgrey = { 29, 29, 27, 255};
    Color yellow = { 243, 216, 63, 255};
    int offset = 50;
    const int screenWidth = 750;
    const int screenHeight = 700;
    float shipOffset = 50.0;
    
    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    //Texture2D livesImage = LoadTexture("img/spaceship.png");

    InitWindow(screenWidth + offset, screenHeight + 2 * offset, "SPACE INVADERS");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();

        BeginDrawing();

        ClearBackground(darkgrey); 
        DrawRectangleRoundedLines({10, 10, float(screenWidth + offset - 20), float(screenHeight + 2 * offset - 20)}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        if(game.run) {
             DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } 
        else
        {
             DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);           
        }
       
        for (int i = 0; i < game.lives; i++)
        {
            
            //DrawTextureV(spaceshipImage, {shipOffset + shipOffset * i, 745}, WHITE);
        }

        game.Draw();



        EndDrawing();
    }

    CloseWindow();

    return 0;
}