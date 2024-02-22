#include <raylib.h>
#include "game.hpp"
#include "ui.hpp"
#include <cstring>
#include <string>


int main()
{
    int offset = 50;
    const int screenWidth = 750;
    const int screenHeight = 700;
    float shipOffset = 50.0;

    InitWindow(screenWidth + offset, screenHeight + 2 * offset, "SPACE INVADERS");
    SetTargetFPS(60);
    InitAudioDevice();

    Game game;
    UI ui;

    while (!WindowShouldClose())
    {
        
        game.HandleInput();
        game.Update();

        BeginDrawing();

        ui.DrawBaseUI(screenWidth, screenHeight, offset, game.score, game.highscore);
        game.Draw();

        if (game.gameState == 0)
        {
            ui.DrawStart();  

        }
        else if(game.gameState == 1) {
            //UpdateMusicStream(game.music);
            ui.DrawLevel(game.level);

        } 
        else if (game.gameState == 2)
        {          
            ui.DrawGameOver(game.score, game.highscore);

        }
        else if (game.gameState == 3)
        {
            ui.DrawPause();

        }
        else if (game.gameState == 4)
        {
            ui.DrawBoss();

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