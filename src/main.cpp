#include <raylib.h>
#include "game.hpp"

#include <cstring>
#include <string>


int main()
{
    int offsetMain = 50;
    const int screenWidthMain = 750;
    const int screenHeightMain = 700;

    InitWindow(screenWidthMain + offsetMain, screenHeightMain + 2 * offsetMain, "SPACE INVADERS");
    SetTargetFPS(60);
    InitAudioDevice();
    
    Game game;

    while (!WindowShouldClose())
    {
        
        game.HandleInput();
        game.Update();

        BeginDrawing();
        game.Draw();
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}