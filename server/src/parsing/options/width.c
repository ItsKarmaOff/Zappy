/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The width.c
*/
/**
 * @file width.c
 * @brief The width.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_width(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -x (or --width) option");
    server->game.game_settings.width =
        my_get_number(parsing->argv[parsing->index + 1], DEFAULT_NB);
    if (my_errno != SUCCESS || server->game.game_settings.width <= 0)
        EXCEPTION("Invalid argument for -x (or --width) option, "
            "it must be a number greater than 0");
    parsing->index += 1;
}
