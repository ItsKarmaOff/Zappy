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
        _playButton = {};
    }

    Rectangle &MenuInfo::getPlayButton(void)
    {
        return _playButton;
    }
}