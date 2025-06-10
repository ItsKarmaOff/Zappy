/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The height.c
*/
/**
 * @file height.c
 * @brief The height.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_height(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -y (or --height) option\n");
    server->game.game_settings.height =
        my_get_number(parsing->argv[parsing->index + 1], DEFAULT_NB);
    if (my_errno != SUCCESS || server->game.game_settings.height <= 0)
        EXCEPTION("Invalid argument for -y (or --height) option, "
            "it must be a number greater than 0\n");
    parsing->index += 1;
}
