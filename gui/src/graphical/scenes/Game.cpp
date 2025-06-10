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
        drawTeams();

    }

    void Graphics::drawGameMap(void)
    {
        for (auto &[k, tile] : _game->getTiles()) {
            tile.draw(_assetsManager.getModels(), _assetsManager.getModelsScale());
        }
    }
    void Graphics::drawTeams(void)
    {
        // Define an array of colors for teams
        Color teamColors[] = {
            RED, BLUE, GREEN, YELLOW, ORANGE, PURPLE, PINK, LIME,
            SKYBLUE, VIOLET, BROWN, DARKGREEN, MAGENTA, GOLD
        };

        // Select a random color for each team
        static std::map<std::string, Color> teamColorMap;
        if (teamColorMap.empty()) {
            for (auto &[key, team] : _game->getTeams()) {
                int randomIndex = GetRandomValue(0, sizeof(teamColors) / sizeof(Color) - 1);
                teamColorMap[key] = teamColors[randomIndex];
            }
        }

        int i = 0;
        for (auto &[key, team] : _game->getTeams()) {
            // draw team name
            float textHeight = 40;
            float textWidth = MeasureText(key.c_str(), textHeight);
            DrawText(key.c_str(), GetScreenWidth() - textWidth - 10, 0 + i * textHeight, textHeight, teamColorMap[key]);
            // draw team player
            for (auto &[id, player] : team.getPlayers()) {
                DEBUG_CONCAT << "Player " << id;
                if (_game->getTiles().contains({player->getPos().x, player->getPos().y})) {
                    TileInfo &tile =_game->getTiles()[{player->getPos().x, player->getPos().y}];
                    DrawModel(_assetsManager.getModels()["player"], tile.getPos(), _assetsManager.getModelsScale()["player"], teamColorMap[key]);
                    DEBUG_CONCAT << "player draw";
                }
            }
        }
    }
}