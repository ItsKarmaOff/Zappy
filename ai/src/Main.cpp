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
    try {
        Parser parser(argc, argv);
        Engine engine(parser);
        engine.run();
    } catch (const Lib::Exceptions::Success &e) {
        if (!std::string(e.what()).empty())
            DEBUG << "SUCCESS: " << e.what();
        return 0;
    } catch (const Lib::Exceptions::Critical &e) {
        if (!std::string(e.what()).empty())
            ERROR << "CRITICIAL: " << e.what();
        return 84;
    } catch (const std::exception &e) {
        if (!std::string(e.what()).empty())
            ERROR << "EXCEPTION: " << e.what();
        return 84;
    }
    return 0;
}
