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
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), CLITERAL(Color){ 130, 130, 130, 100 });
        int size = MeasureText("SCOREBOARD", 50);
        DrawText("SCOREBOARD", GetScreenWidth() / 2 - size / 2, 0, 50, RED);

        int i = 0;
        for (auto &[id, player] : _game->getPlayers()) {
            int fontSize = 30;
            std::ofstream stream; stream << "Player: " << id;
            std::stringstream str; str << stream.rdbuf();
            DrawText(str.str().c_str(), 0, i * fontSize, 30, player->getColor());
        }
    }
}