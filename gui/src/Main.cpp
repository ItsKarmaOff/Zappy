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
    } catch (const Lib::Exceptions::Success &e) {
        if (!std::string(e.what()).empty())
            DEBUG << "SUCCESS: " << e.what();
        return 0;
    } catch (const Lib::Exceptions::Critical &e) {
        if (!std::string(e.what()).empty())
            ERROR << "CRITICAL: " << e.what();
        return 84;
    } catch (const std::exception &e) {
        if (!std::string(e.what()).empty())
            ERROR << "EXCEPTION: " << e.what();
        return 84;
    }
    return 0;
}
