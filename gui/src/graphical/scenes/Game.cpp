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
        if (IsKeyPressed('Z')) {
            _game->getCamera().target =
            { _game->getMapSize().x / 2, 0.0f, _game->getMapSize().y / 2 };
        }
    }

    void Graphics::updateGame(void)
    {
        UpdateCamera(&_game->getCamera(), CAMERA_FREE);
    }

    void Graphics::drawGame(void)
    {
        ClearBackground(RAYWHITE);

        BeginMode3D(_game->getCamera());
        drawGameMap();
        EndMode3D();
    }

    void Graphics::drawGameMap(void)
    {
        for (int i = 0; i < _game->getMapSize().x; i++) {
            for (int j = 0; j < _game->getMapSize().y; j++) {
                DrawCube({(float)i, 0, (float)j}, 1.0f, 1.0f, 1.0f, SKYBLUE);
                DrawCubeWires({(float)i, 0.0f, (float)j}, 1.0f, 1.0f, 1.0f, BLACK);
            }
        }
    }
}