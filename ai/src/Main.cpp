/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The main function of the ai
*/
/**
 * @file Main.cpp
 * @brief The main function of the ai
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "Lib.hpp"
#include "Parser.hpp"
#include "Engine.hpp"

int main(int argc, char **argv)
{
    Parser parser;
    try {
        parser.parse(argc, argv);
    } catch (const Lib::Exceptions::Critical &e) {
        Lib::Logs::Error() << e.what();
        return 84;
    } catch (const Lib::Exceptions::Help &e) {
        std::cout << e.what();
        return 0;
    }
    try {
        Engine engine(parser);
        engine.run();
    } catch (...) {
        return 0;
    }
    return 0;
}
