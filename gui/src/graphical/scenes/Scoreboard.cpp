/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Scoreboard scene implementation
*/
/**
 * @file Scoreboard.cpp
 * @brief The Scoreboard scene implementation
 */

#include "Graphics.hpp"

namespace Gui {
    int titleSize = GetScreenHeight() / 10;
    int tabSize = GetScreenHeight() / 20;
    int textSize = GetScreenHeight() / 30;

    void Graphics::handleEventsScoreboard()
    {
        if (IsKeyPressed(KEY_SPACE)) {
            DEBUG << "troufion";
        }
        if (IsKeyPressed(KEY_TAB)) {
            _scene = GAME;
            DisableCursor();
        }
        if (IsKeyReleased(KEY_ESCAPE)) {
            switchToPause(SCOREBOARD);
        }
    }

    void Graphics::updateScoreboard()
    {
        titleSize = GetScreenHeight() / 10;
        tabSize = GetScreenHeight() / 20;
        textSize = GetScreenHeight() / 30;
        if (!IsMusicStreamPlaying(SoundsManager::getInstance().getMusics()[SoundsManager::GAME_SONG]))
            PlayMusicStream(SoundsManager::getInstance().getMusics()[SoundsManager::GAME_SONG]);
        UpdateMusicStream(SoundsManager::getInstance().getMusics()[SoundsManager::GAME_SONG]);
        // UpdateCamera(&_game->getCamera(), CAMERA_FREE);
    }

    void Graphics::drawScoreboard()
    {
        ClearBackground(RAYWHITE);
        drawGame();
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), CLITERAL(Color){ 130, 130, 130, 100});
        int size = MeasureText("SCOREBOARD", titleSize);
        DrawText("SCOREBOARD", GetScreenWidth() / 2 - size / 2, 0, titleSize, RED);

        int i = 0;
        for (auto &[id, player] : _game->getPlayers()) {
            if (player->getTeamName() == "UnknownTeam")
                continue;
            std::stringstream str;
            str << "Player#" << id;
            int y = titleSize + tabSize + i * textSize;
            DrawText(str.str().c_str(), 0, y, textSize, player->getColor());
            DrawText(std::to_string(player->getLevel()).c_str(), GetScreenWidth() / 4, y, textSize, player->getColor());
            DrawText(player->getTeamName().c_str(), GetScreenWidth() * 2 / 4, y, textSize, player->getColor());
            i++;
        }
        drawTabs();
    }

    void Graphics::drawTabs()
    {
        std::string id("ID");
        std::string level("LEVEL");
        std::string team("TEAM");
        DrawText(id.c_str(), 0, GetScreenHeight() / 10, tabSize, MAROON);
        DrawText(level.c_str(), GetScreenWidth() / 4, GetScreenHeight() / 10, tabSize, MAROON);
        DrawText(team.c_str(), GetScreenWidth() * 2 / 4, GetScreenHeight() / 10, tabSize, MAROON);

    }
}