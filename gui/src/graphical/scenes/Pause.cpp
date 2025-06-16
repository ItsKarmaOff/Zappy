/*
** EPITECH PROJECT, 2025
** Pause.cpp
** File description:
** Pause in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical/scenes
*/

#include "Graphics.hpp"
#include "PauseInfo.hpp"
#include <raylib.h>

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
                    _pause->setTimeUnit(_pause->getTimeUnit() + 1);
                    _queueManager->pushCommand({"sst", std::to_string(_pause->getTimeUnit())});
                } else if (_pause->getButtonsSettings()[PauseInfo::MINUS_BUTTON].isMouseOver(_mousePos)) {
                    if (_pause->getTimeUnit() > 1) {
                        _pause->setTimeUnit(_pause->getTimeUnit() - 1);
                        _queueManager->pushCommand({"sst", std::to_string(_pause->getTimeUnit())});
                    }

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
        _pause->draw();
    }

}