#include "inputhandler.hpp"
#include "game.hpp"

void InputHandler::HandleInput(Game& game)
{
    if 
    (IsKeyPressed(KEY_I))
    {
        game.info = !game.info;
    }

    if (IsKeyPressed(KEY_P))
    {
        game.pauseMusic = !game.pauseMusic;

        if (game.pauseMusic) PauseMusicStream(game.music);
        else ResumeMusicStream(game.music);
        if (game.pauseMusic) PauseMusicStream(game.bossMusic);
        else ResumeMusicStream(game.bossMusic);
    }

    if(IsKeyDown(49))
    {
        if(game.gameState == 0 || game.gameState == 2)
        {
            game.Init();
            game.Reset();
            game.level = 2;
            game.NextLevel();
        }
    }

    if (IsKeyPressed(KEY_ENTER))
    {
        if(game.gameState == 0 || game.gameState == 2)
        {
            game.Init();
            game.Reset();
            game.NextLevel();
        } 
        else if (game.gameState == 3)
        {
            game.gameState = game.activeGameState;
        }
        else if (game.gameState == 1 || game.gameState == 4 || game.gameState == 5)
        {
            game.gameState = 3;
        }

    }

    if(game.gameState == 1 || game.gameState == 4 || game.gameState == 5){
        if (IsKeyDown(KEY_LEFT))
        {
            game.spaceship.MoveLeft();
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            game.spaceship.MoveRight();
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            game.spaceship.FireLaser();
        }
        
    }

}