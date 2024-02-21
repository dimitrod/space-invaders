#include <raylib.h>
#include "game.hpp"


int main()
{
    Color darkgrey = { 29, 29, 27, 255};
    const int screenWidth = 750;
    const int screenHeight = 700;
    

    InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
    SetTargetFPS(60);

    Game game;

    while (!WindowShouldClose())
    {
        game.HandleInput();
        game.Update();

        BeginDrawing();

        ClearBackground(darkgrey); 
        game.Draw();



        EndDrawing();
    }

    CloseWindow();

    return 0;
}