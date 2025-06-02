/*
** EPITECH PROJECT, 2025
** Menu.cpp
** File description:
** Menu in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical/scenes
*/

#include "Graphics.hpp"
#include <raylib.h>

namespace Gui {
    void Graphics::handleEventsMenu(void)
    {
        if (IsKeyReleased(KEY_SPACE)) {
            _scene = GAME;
            if (!_game)
                _game = std::make_shared<GameInfo>();
            DisableCursor();
        }
    }

    void Graphics::updateMenu(void)
    {

    }

    void Graphics::drawMenu(void)
    {
        ClearBackground(RAYWHITE);
        DrawText("Press SPACE gros fils de pute !", GetScreenWidth() / 2 - 20, GetScreenHeight() / 2, 34, DARKPURPLE);
        // DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color)
    }
}