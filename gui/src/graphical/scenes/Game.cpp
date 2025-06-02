/*
** EPITECH PROJECT, 2025
** Game.cpp
** File description:
** Game in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical/scenes
*/

#include "Graphics.hpp"
#include <raylib.h>

namespace Gui {
    void Graphics::handleEventsGame(void)
    {
        if (IsKeyReleased(KEY_SPACE)) {
            _scene = MENU;
            EnableCursor();
        }
        // on peut pas modifier la touche
        if (IsKeyPressed('Z'))
            _game->getCamera().target = { 0.0f, 0.0f, 0.0f };
    }

    void Graphics::updateGame(void)
    {
        UpdateCamera(&_game->getCamera(), CAMERA_FREE);
    }

    void Graphics::drawGame(void)
    {
        ClearBackground(RAYWHITE);

        BeginMode3D(_game->getCamera());
        DrawCube({0, 0, 0}, 2, 2, 2, DARKBLUE);
        DrawGrid(10, 1.0f);
        EndMode3D();
    }
}