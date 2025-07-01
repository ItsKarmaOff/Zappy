/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "version" option
*/
/**
 * @file version.c
 * @brief The file containing the function for the "version" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void option_version(UNUSED server_t *server, UNUSED parsing_t *parsing)
{
    my_putstr(BOLD "VERSION:" ENDL
        "\tZappy Server version 1.0.0\n"
        "\tBuilt on: " __DATE__ " at " __TIME__ "\n");
    my_exit(SUCCESS, "");
}
