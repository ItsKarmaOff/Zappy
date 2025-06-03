/*
** EPITECH PROJECT, 2025
** MenuInfo.cpp
** File description:
** MenuInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "MenuInfo.hpp"
#include <raylib.h>

namespace Gui {
    MenuInfo::MenuInfo()
    {
        float width = GetScreenWidth() / 5;
        float height = GetScreenHeight() / 10;

        _buttons = {
        Button({
            GetScreenWidth() / 2 - width / 2,
            (GetScreenHeight() / 2 - height / 2)},
            {width, height}), // Play button
        Button({
            GetScreenWidth() / 2 - width / 2,
            (GetScreenHeight() / 2 - height / 2) + height},
            {width, height}) // Exit button
        };

        _buttons[PLAY_BUTTON].setText("Play", SKYBLUE);
        _buttons[EXIT_BUTTON].setText("Exit", MAROON);
        _buttons[PLAY_BUTTON].setColors({GREEN, DARKGRAY}); // Default colors for play button
        _buttons[EXIT_BUTTON].setColors({RED, DARKGRAY}); // Default colors for exit button
    }


    std::vector<Button>& MenuInfo::getButtons()
    {
        return _buttons;
    }

}