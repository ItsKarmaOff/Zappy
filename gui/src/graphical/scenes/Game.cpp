/*
** EPITECH PROJECT, 2025
** Game.cpp
** File description:
** Game in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical/scenes
*/

#include "Graphics.hpp"
#include "TileInfo.hpp"
#include "Logs.hpp"
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
            { _game->getMapSize().x / 2 * TILE_SIZE, 0.0f, _game->getMapSize().y / 2 * TILE_SIZE };
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
        for (auto &[k, tile] : _game->getTiles()) {
            tile.draw(_assetsManager.getModels(), _assetsManager.getModelsScale());
        }
    }
}