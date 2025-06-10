/*
** EPITECH PROJECT, 2025
** Scoreboard.cpp
** File description:
** Scoreboard in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical/scenes
*/

#include "Graphics.hpp"
#include "Logs.hpp"
#include <raylib.h>
#include <streambuf>

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
    }

    void Graphics::updateScoreboard()
    {
        titleSize = GetScreenHeight() / 10;
        tabSize = GetScreenHeight() / 20;
        textSize = GetScreenHeight() / 30;
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
            std::stringstream str;
            str << "Player" << id;
            DrawText(str.str().c_str(), 0, titleSize + tabSize + i * textSize, textSize, player->getColor());
            i++;
        }
        drawTabs();
    }

    void Graphics::drawTabs()
    {
        std::string id("ID");
        std::string level("LEVEL");
        DrawText(id.c_str(), 0, GetScreenHeight() / 10, tabSize, MAROON);
        DrawText(level.c_str(), GetScreenWidth() / 4, GetScreenHeight() / 10, tabSize, MAROON);
    }
}