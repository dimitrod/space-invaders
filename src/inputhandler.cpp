#include "inputhandler.hpp"


void InputHandler::InfoPressed()
{
    if (IsKeyPressed(KEY_I))
    {
        info = !info;
    }
}