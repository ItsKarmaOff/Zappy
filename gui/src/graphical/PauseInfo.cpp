/*
** EPITECH PROJECT, 2025
** PauseInfo.cpp
** File description:
** PauseInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "PauseInfo.hpp"
#include "AssetsManager.hpp"
#include <algorithm>
#include <map>
#include <raylib.h>

namespace Gui {
    PauseInfo::PauseInfo()
        : _updateBackgroundCallback(nullptr), _drawBackgroundCallback(nullptr),
        _volume(100)
    {
        _timeUnit = 1;
        _currentSubscene = RESUME;
        _buttons = {
        Button("Resume"),
        Button("Settings"),
        Button("Exit"),
        };
        _buttons[RESUME_BUTTON].setColors({DARKBLUE, BLUE});
        _buttons[SETTINGS_BUTTON].setColors({ORANGE, GOLD});
        _buttons[QUIT_BUTTON].setColors({MAROON, RED});

        _buttonsSettings = {
            Button("Time Unit: "),
            Button("+"),
            Button("-"),
        };
        _buttonsSettings[TIME_UNIT_BUTTON].setColors({WHITE, WHITE});
        _buttonsSettings[PLUS_BUTTON].setColors({DARKGREEN, GREEN});
        _buttonsSettings[MINUS_BUTTON].setColors({DARKGREEN, GREEN});
        _buttonsMap = {
            {RESUME, &_buttons},
            {SETTINGS, &_buttonsSettings},
            {QUIT, &_buttons}
        };
    }

    PauseInfo::~PauseInfo()
    {
        // Cleanup if necessary
    }

    void PauseInfo::setBackgroundCallbacks(std::function<void()> updateCallback,
                                           std::function<void()> drawCallback)
    {
        _updateBackgroundCallback = std::move(updateCallback);
        _drawBackgroundCallback = std::move(drawCallback);
    }

    void PauseInfo::resetCallbacks()
    {
        _updateBackgroundCallback = nullptr;
        _drawBackgroundCallback = nullptr;
    }

    ////////////////////////////////////// UPDATERS //////////////////////////////////////
    void PauseInfo::updateButtons(std::vector<Button> &buttons)
    {
        float width = GetScreenWidth() / 5;
        float height = GetScreenHeight() / 10;
        Vector2 buttonSize = {width, height};
        Vector2 buttonPosition = {
            GetScreenWidth() / 2 - width / 2,
            GetScreenHeight() / 2 - height / 2
        };

        for (auto &button : buttons)
            button.switchColorsIfHover(GetMousePosition());

        int i = 0;
        for (auto &button : buttons) {
            button.setPosition({buttonPosition.x, buttonPosition.y + (i * height)});
            button.setSize(buttonSize);
            i++;
        }
    }

    void PauseInfo::updateSettingsButtons(std::vector<Button> &buttons)
    {
        float width = GetScreenWidth() / 5;
        float height = GetScreenHeight() / 10;
        Vector2 buttonSize = {width, height};
        Vector2 buttonPosition = {
            GetScreenWidth() / 2 - width / 2,
            GetScreenHeight() / 2 - height / 2
        };
        _buttonsSettings[TIME_UNIT_BUTTON].setText("Time: " + std::to_string(_timeUnit));
        _buttonsSettings[TIME_UNIT_BUTTON].setSize({width * 3 / 4.f, height});
        _buttonsSettings[TIME_UNIT_BUTTON].setPosition({buttonPosition.x, buttonPosition.y});

        float smallButtonWidth = width / 4.f;
        float smallButtonHeight = height / 2.f;
        Vector2 plusButtonPosition = {
            buttonPosition.x + width - smallButtonWidth,
            buttonPosition.y
        };
        Vector2 minusButtonPosition = {
            buttonPosition.x + width - smallButtonWidth,
            buttonPosition.y + smallButtonHeight
        };

        // PLUS button
        _buttonsSettings[PLUS_BUTTON].setSize({smallButtonWidth, smallButtonHeight});
        _buttonsSettings[PLUS_BUTTON].setPosition(plusButtonPosition);

        // MINUS button
        _buttonsSettings[MINUS_BUTTON].setSize({smallButtonWidth, smallButtonHeight});
        _buttonsSettings[MINUS_BUTTON].setPosition(minusButtonPosition);
    }

    void PauseInfo::update()
    {
        if (_updateBackgroundCallback) {
            _updateBackgroundCallback();
        }
        if (_currentSubscene == SETTINGS) {
            updateSettingsButtons(_buttonsSettings);
        } else
            updateButtons(*_buttonsMap[_currentSubscene]);
    }

    ////////////////////////////////////// DRAWERS //////////////////////////////////////
    void PauseInfo::drawButtons(std::vector<Button> &buttons)
    {
        for (auto &button : buttons) {
            button.switchColorsIfHover(GetMousePosition());
            Vector2 textPos = button.getCenteredPositionForText(button.getSize().y / 2);
            DrawRectangleRounded(button.getButton(), 0.2, 1.0f, button.getCurrentColor());
            DrawText(button.getText().c_str(), textPos.x, textPos.y, button.getSize().y / 2, button.getTextColor());
        }
    }

    void PauseInfo::drawVolumeSlider()
    {
        float width = GetScreenWidth() / 5;
        float height = GetScreenHeight() / 10;
        Vector2 buttonSize = {width, height};
        Vector2 buttonPosition = {
            GetScreenWidth() / 2 - width / 2,
            GetScreenHeight() / 2 - height / 2
        };

        Rectangle sliderBar = {buttonPosition.x, buttonPosition.y + (height + (height / 2)), buttonSize.x, buttonSize.y / 2};
        float knobWidth = (height / 2);
        float knobHeight = (height / 2) * 1.5f;


        float knobPos = buttonPosition.x + (_volume / 100.0f) * buttonSize.x;
        Rectangle knob = {knobPos - knobWidth / 2, sliderBar.y - (knobHeight - sliderBar.height) / 2, knobWidth, knobHeight};


        DrawRectangleRec(sliderBar, WHITE);
        DrawRectangleRec(knob, DARKBLUE);
        DrawText(TextFormat("Volume: %d", _volume), buttonPosition.x, buttonPosition.y + height, buttonSize.y / 2, WHITE);
    }


    void PauseInfo::draw(AssetsManager &assetsManager)
    {
        if (_drawBackgroundCallback) {
            _drawBackgroundCallback();
        }
        float scaleX = static_cast<float>(GetScreenWidth()) / AssetsManager::getTextures()["blur"]->width;
        float scaleY = static_cast<float>(GetScreenHeight()) / AssetsManager::getTextures()["blur"]->height;
        float scale = std::max(scaleX, scaleY);
        DrawTextureEx(*assetsManager.getTextures()["blur"], {0, 0}, 0, scale, WHITE);
        drawButtons(*_buttonsMap[_currentSubscene]);
        if (_currentSubscene == SETTINGS)
            drawVolumeSlider();
    }

    ////////////////////////////////////// GETTERS //////////////////////////////////////


    PauseInfo::PauseSubscene PauseInfo::getCurrentSubscene() const
    {
        return _currentSubscene;
    }

    void PauseInfo::setCurrentSubscene(PauseSubscene action)
    {
        _currentSubscene = action;
    }

    std::vector<Button> &PauseInfo::getButtons()
    {
        return _buttons;
    }

    std::vector<Button> &PauseInfo::getButtonsSettings()
    {
        return _buttonsSettings;
    }
    const int& PauseInfo::getTimeUnit() const
    {
        return _timeUnit;
    }

    void PauseInfo::setTimeUnit(int timeUnit)
    {
        _timeUnit = timeUnit;
    }

    int PauseInfo::getVolume() const
    {
        return _volume;
    }

    void PauseInfo::setVolume(int volume)
    {
        _volume = volume;
    }

}