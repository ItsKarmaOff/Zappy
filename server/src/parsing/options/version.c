/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The version.c
*/
/**
 * @file version.c
 * @brief The version.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_version(UNUSED server_t *server, UNUSED parsing_t *parsing)
{
    my_putstr(BOLD "VERSION:" ENDL
        "\tZappy Server version 1.0.0\n"
        "\tBuilt on: " __DATE__ " at " __TIME__ "\n");
    my_exit(SUCCESS, "");
}
