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
        // UpdateCamera(&_game->getCamera(), CAMERA_FREE);
    }

    void Graphics::drawScoreboard()
    {
        ClearBackground(RAYWHITE);
        drawGame();
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), CLITERAL(Color){ 130, 130, 130, 100});
        int height = GetScreenHeight() / 10;

        int size = MeasureText("SCOREBOARD", height);
        DrawText("SCOREBOARD", GetScreenWidth() / 2 - size / 2, 0, height, RED);
        drawTabs();

        int i = 0;
        for (auto &[id, player] : _game->getPlayers()) {
            int fontSize = GetScreenHeight() / 25;
            std::stringstream str;
            str << "Player" << id;
            DrawText(str.str().c_str(), 0, GetScreenHeight() / 10 + 20 + i * fontSize, fontSize, player->getColor());
        }
    }
    void Graphics::drawTabs()
    {
        int height = GetScreenHeight() / 20;
        std::string id("ID");
        std::string level("LEVEL");
        DrawText(id.c_str(), 0, GetScreenHeight() / 10, height, MAROON);
        DrawText(level.c_str(), GetScreenWidth() / 4, GetScreenHeight() / 10, height, MAROON);
    }
}