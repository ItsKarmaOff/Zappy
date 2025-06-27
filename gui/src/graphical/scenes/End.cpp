/*
** EPITECH PROJECT, 2025
** End.cpp
** File description:
** End in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical/scenes
*/

#include "EndInfo.hpp"
#include "Graphics.hpp"
#include <raylib.h>

namespace Gui {
    void Graphics::handleEventsEnd(void)
    {
        if (!_end) {
            _end = std::make_shared<EndInfo>();
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            _windowShouldRun = false;
        }
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (_end->buttons[EndInfo::RESTART].isMouseOver(_mousePos)) {
                _scene = MENU;
            }
            if (_end->buttons[EndInfo::EXIT].isMouseOver(_mousePos)) {
                _windowShouldRun = false;
            }
        }

    }

    void Graphics::updateEnd(void)
    {
        for (auto &[k, button] : _end->buttons)
            button.switchColorsIfHover(_mousePos);

        float width = GetScreenWidth() / 5.f;
        float height = GetScreenHeight() / 10.f;

        _end->buttons[EndInfo::RESTART].setPosition({
            GetScreenWidth() / 2.f - width / 2,
            (GetScreenHeight() / 2.f - height / 2)
        });
        _end->buttons[EndInfo::EXIT].setPosition({
            GetScreenWidth() / 2.f - width / 2,
            (GetScreenHeight() / 2.f - height / 2) + height
        });
        _end->buttons[EndInfo::RESTART].setSize({width, height});
        _end->buttons[EndInfo::EXIT].setSize({width, height});
    }

    void Graphics::drawEnd(void)
    {
        ClearBackground(RAYWHITE);
        float scaleX = static_cast<float>(GetScreenWidth()) / _assetsManager.getTextures()["menu"]->width;
        float scaleY = static_cast<float>(GetScreenHeight()) / _assetsManager.getTextures()["menu"]->height;
        float scale = std::max(scaleX, scaleY);
        DrawTextureEx(*_assetsManager.getTextures()["menu"], {0, 0}, 0, scale, WHITE);

        int fontSize = GetScreenHeight() / 10;
        int textSize = MeasureText(_end->winner.c_str(), fontSize);
        Vector2 textPosition = {
            GetScreenWidth() / 2.f - textSize / 2.f,
            GetScreenHeight() / 3.f
        };
        DrawText(_end->winner.c_str(), textPosition.x, textPosition.y, fontSize, _end->teamColor);


        for (const auto &button : _end->buttons) {
            DrawRectangleRounded(button.second.getButton(), 0.2f, 1, button.second.getCurrentColor());
            if (!button.second.getText().empty()) {
                Vector2 textPos = button.second.getCenteredPositionForText(button.second.getSize().y / 2);
                DrawText(button.second.getText().c_str(), textPos.x, textPos.y, button.second.getSize().y / 2, button.second.getTextColor());
            }
        }
    }
}
