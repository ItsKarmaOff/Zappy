/*
** EPITECH PROJECT, 2025
** Menu.cpp
** File description:
** Menu in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical/scenes
*/

#include "Graphics.hpp"
#include "Commands.hpp"
#include "Logs.hpp"
#include "SoundsManager.hpp"
#include <raylib.h>

namespace Gui {
    void Graphics::handleEventsMenu(void)
    {
        if (!_menu) {
            _menu = std::make_shared<MenuInfo>();
        }
        for (auto &button : _menu->getButtons()) {
            button.setCurrentColor(button.isMouseOver(_mousePos) ? button.getColors().second : button.getColors().first);
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
            if (_menu->getButtons()[MenuInfo::PLAY_BUTTON].isMouseOver(_mousePos)) {
                _scene = GAME;
                if (!_game) {
                    _assetsManager.loadAssets();
                    _game = std::make_shared<GameInfo>();
                    _chatbox = std::make_shared<Chatbox>();
                }
                if (state == WELCOME_STATE) {
                    _queueManager->pushCommand({"GRAPHIC"});
                    state = TEAM_NAME;
                }
                DisableCursor();
                StopMusicStream(SoundsManager::getInstance().getMusics()[SoundsManager::MENU_SONG]);
            }
            if (_menu->getButtons()[MenuInfo::EXIT_BUTTON].isMouseOver(_mousePos)) {
                _windowShouldRun = false;
                StopMusicStream(SoundsManager::getInstance().getMusics()[SoundsManager::MENU_SONG]);
            }
        }
    }

    void Graphics::updateMenu(void)
    {
        if (!IsMusicStreamPlaying(SoundsManager::getInstance().getMusics()[SoundsManager::MENU_SONG]))
            PlayMusicStream(SoundsManager::getInstance().getMusics()[SoundsManager::MENU_SONG]);
        UpdateMusicStream(SoundsManager::getInstance().getMusics()[SoundsManager::MENU_SONG]);
        float width = GetScreenWidth() / 5;
        float height = GetScreenHeight() / 10;

        _menu->getButtons()[MenuInfo::PLAY_BUTTON].setPosition({
            GetScreenWidth() / 2 - width / 2,
            (GetScreenHeight() / 2 - height / 2)
        });
        _menu->getButtons()[MenuInfo::EXIT_BUTTON].setPosition({
            GetScreenWidth() / 2 - width / 2,
            (GetScreenHeight() / 2 - height / 2) + height
        });
        _menu->getButtons()[MenuInfo::PLAY_BUTTON].setSize({width, height});
        _menu->getButtons()[MenuInfo::EXIT_BUTTON].setSize({width, height});
    }

    void Graphics::drawMenu(void)
    {
        ClearBackground(RAYWHITE);
        float scaleX = static_cast<float>(GetScreenWidth()) / _assetsManager.getTextures()["menu"]->width;
        float scaleY = static_cast<float>(GetScreenHeight()) / _assetsManager.getTextures()["menu"]->height;
        float scale = std::max(scaleX, scaleY);
        DrawTextureEx(*_assetsManager.getTextures()["menu"], {0, 0}, 0, scale, WHITE);

        for (const auto &button : _menu->getButtons()) {
            DrawRectangleRounded(button.getButton(), 0.2f, 1, button.getCurrentColor());
            if (!button.getText().empty()) {
                Vector2 textPos = button.getCenteredPositionForText(button.getSize().y / 2);
                DrawText(button.getText().c_str(), textPos.x, textPos.y, button.getSize().y / 2, button.getTextColor());
            }
        }
    }
}