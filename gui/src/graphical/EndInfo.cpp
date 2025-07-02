/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The EndInfo class implementation
*/
/**
 * @file EndInfo.cpp
 * @brief The EndInfo class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
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
