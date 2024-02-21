#include <raylib.h>
#include "game.hpp"


int main()
{
    Color darkgrey = { 29, 29, 27, 255};
    Color yellow = { 243, 216, 63, 255};
    int offset = 50;
    const int screenWidth = 750;
    const int screenHeight = 700;
    

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
        game.Draw();



        EndDrawing();
    }

    CloseWindow();

    return 0;
}