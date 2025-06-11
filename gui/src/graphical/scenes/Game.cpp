/*
** EPITECH PROJECT, 2025
** Game.cpp
** File description:
** Game in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical/scenes
*/

#include "Graphics.hpp"
#include "TileInfo.hpp"
#include "Logs.hpp"
#include <chrono>
#include <raylib.h>
#include <raymath.h>

namespace Gui {
    void Graphics::handleEventsGame(void)
    {
        // on peut pas modifier la touche, mais Z = W (dcp faut appuyer sur W)
        if (IsKeyPressed(KEY_Z)) {
            _game->getCamera().target =
            { _game->getMapSize().x / 2 * TILE_SIZE, 0.0f, _game->getMapSize().y / 2 * TILE_SIZE };
        }
        if (IsKeyPressed(KEY_TAB)) {
            _scene = SCOREBOARD;
            EnableCursor();
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
        drawPlayers();
        DrawModel(_assetsManager.getModels()["background"]->getModel(), {0, 0, 0}, _assetsManager.getModels()["background"]->getScale(), WHITE);
        EndMode3D();
        drawTeams();

    }

    void Graphics::drawGameMap(void)
    {
        for (auto &[k, tile] : _game->getTiles()) {
            tile.draw(_assetsManager);
        }
    }
    void Graphics::drawTeams(void)
    {
        int i = 0;
        for (auto &[key, team] : _game->getTeams()) {
            // draw team name
            float textHeight = 40;
            float textWidth = MeasureText(key.c_str(), textHeight);
            DrawText(key.c_str(), GetScreenWidth() - textWidth - 10, 0 + i * textHeight, textHeight, team.getColor());
            i++;
        }
    }
    void Graphics::drawPlayers(void)
    {
        for (auto &[id, player] : _game->getPlayers()) {
            if (!_game->getTiles().contains({player->getPos().x, player->getPos().y})) {
                ERROR << "No tile matching the player position.";
                return;
            }
            TileInfo &tile =_game->getTiles()[{player->getPos().x, player->getPos().y}];
            _assetsManager.getModels()["player"]->getModel().transform = MatrixRotateY(DEG2RAD * (90 * player->getOrientation()));

            DrawModel(_assetsManager.getModels()["player"]->getModel(), {tile.getPos().x, 2, tile.getPos().z}, _assetsManager.getModels()["player"]->getScale(), player->getColor());

            // debugging broadcast message
            if (!player->getMessagesToBroadcast().empty()) {
                std::string msg = player->getMessagesToBroadcast().front();
                std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();

                // Store message with timestamp if it's new
                if (!player->isBroadcasting()) {
                    player->getClock() = currentTime;
                    player->setBroadcasting(true);
                } else {
                    if (player->getClock() - currentTime > std::chrono::seconds(1) ) {
                        player->setBroadcasting(false);
                        player->getMessagesToBroadcast().pop();
                    } else {
                        DEBUG_CONCAT << "player Broadcast: " << msg;
                    }
                }
            }

        }
    }
}