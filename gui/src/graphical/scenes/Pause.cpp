/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The Pause scene implementation
*/
/**
 * @file Pause.cpp
 * @brief The Pause scene implementation
 */

#include "Graphics.hpp"

namespace Gui {

    void Graphics::switchToPreviousScene(void)
    {
        if (_previousScene == GAME) {
            _scene = GAME;
            DisableCursor();
        } else if (_previousScene == SCOREBOARD) {
            _scene = SCOREBOARD;
            EnableCursor();
        }
        _pause->resetCallbacks();
    }

    void Graphics::switchToPause(Scene previousScene)
    {
        if (!_pause)
            _pause = std::make_shared<PauseInfo>();
        _previousScene = previousScene;

        if (previousScene == GAME) {
            _pause->setBackgroundCallbacks(
                [this]() { this->updateGame(); },
                [this]() { this->drawGame(); }
            );
        } else if (previousScene == SCOREBOARD) {
            _pause->setBackgroundCallbacks(
                [this]() { this->updateScoreboard(); },
                [this]() { this->drawScoreboard(); }
            );
        }
        _scene = PAUSE;
        EnableCursor();
    }

    void Graphics::handleEventsPause(void)
    {
        if (_pause->getCurrentSubscene() == PauseInfo::RESUME || _pause->getCurrentSubscene() == PauseInfo::QUIT) {
            if (IsKeyReleased(KEY_ESCAPE))
                switchToPreviousScene();
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                if (_pause->getButtons()[PauseInfo::RESUME_BUTTON].isMouseOver(_mousePos)) {
                    switchToPreviousScene();
                } else if (_pause->getButtons()[PauseInfo::SETTINGS_BUTTON].isMouseOver(_mousePos)) {
                    _pause->setCurrentSubscene(PauseInfo::SETTINGS);
                }
                else if (_pause->getButtons()[PauseInfo::QUIT_BUTTON].isMouseOver(_mousePos)) {
                    _windowShouldRun = false;
                }
            }
        }
        else if (_pause->getCurrentSubscene() == PauseInfo::SETTINGS) {
            if (IsKeyReleased(KEY_ESCAPE))
                _pause->setCurrentSubscene(PauseInfo::RESUME);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (_pause->getButtonsSettings()[PauseInfo::PLUS_BUTTON].isMouseOver(_mousePos)) {
                    _queueManager->pushCommand({"sst", std::to_string(_pause->getTimeUnit() + 1)});
                } else if (_pause->getButtonsSettings()[PauseInfo::MINUS_BUTTON].isMouseOver(_mousePos)) {
                    if (_pause->getTimeUnit() > 1) {
                        _queueManager->pushCommand({"sst", std::to_string(_pause->getTimeUnit() - 1)});
                    }
                }
            }
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                float width = GetScreenWidth() / 5;
                float height = GetScreenHeight() / 10;
                Vector2 buttonSize = {width, height};
                Vector2 buttonPosition = {
                    GetScreenWidth() / 2 - width / 2,
                    GetScreenHeight() / 2 - height / 2
                };

                float sliderY = buttonPosition.y + (height + (height / 2));
                Rectangle sliderArea = {
                    buttonPosition.x,
                    sliderY,
                    buttonSize.x,
                    buttonSize.y / 2
                };
                if (CheckCollisionPointRec(_mousePos, sliderArea)) {
                    float relativeX = _mousePos.x - sliderArea.x;
                    int newVolume = static_cast<int>((relativeX / sliderArea.width) * 100);
                    newVolume = std::clamp(newVolume, 0, 100);
                    _pause->setVolume(newVolume);
                    for (auto &music : SoundsManager::getInstance().getMusics())
                        SetMusicVolume(music.second, newVolume / 100.0f);
                }
            }
        }
    }

    void Graphics::updatePause(void)
    {
        _pause->update();
    }

    void Graphics::drawPause(void)
    {
        _pause->draw(_assetsManager);
    }

}