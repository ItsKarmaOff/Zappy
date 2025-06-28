/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The main function of the GUI
*/
/**
 * @file Main.cpp
 * @brief The main function of the GUI
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
*/

#include "Core.hpp"

int main(int argc, char **argv)
{
    try {
        Gui::Core core(argc, argv);
        core.run();
        return 0;
    } catch (const std::exception &e) {
        ERROR << "EXCEPTION: " << e.what();
        return 84;
    }
}
