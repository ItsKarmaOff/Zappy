/*
** EPITECH PROJECT, 2025
** EndInfo.cpp
** File description:
** EndInfo in ~/Documents/EPITECH/TEK2/YEP/BYEP400_zappy/gui/src/graphical
*/

#include "EndInfo.hpp"

namespace Gui {

    // Default constructor initializes winner to an empty string and teamColor to white
    EndInfo::EndInfo() : winner(""), teamColor(WHITE)
    {
        buttons[RESTART] = Button("Menu").setColors({DARKBLUE, BLUE});
        buttons[EXIT] = Button("Exit").setColors({MAROON, RED});
    }

}
