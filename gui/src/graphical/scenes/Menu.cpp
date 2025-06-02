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
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(_mousePos, _menu->getPlayButton())) {
                _scene = GAME;
                if (!_game)
                    _game = std::make_shared<GameInfo>();
                DisableCursor();
            }
        }
    }

    void Graphics::updateMenu(void)
    {
        float width = GetScreenWidth() / 5;
        float height = GetScreenHeight() / 10;
        _menu->getPlayButton() = {
            GetScreenWidth() / 2 - width / 2,
            GetScreenHeight() / 2 - height / 2,
            width, height
        };
    }

    void Graphics::drawMenu(void)
    {
        ClearBackground(RAYWHITE);
        DrawRectangleRoundedLines(_menu->getPlayButton(), 0.2f, 10, DARKPURPLE);
        DrawText("fdp", GetScreenWidth() / 2 - 20, GetScreenHeight() / 2, _menu->getPlayButton().height / 2, DARKPURPLE);
    }
}