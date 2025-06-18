/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The auto_end.c
*/
/**
 * @file auto_end.c
 * @brief The auto_end.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_auto_end(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -e (or --autoEnd) option");
    my_strlowcase(parsing->argv[parsing->index + 1]);
    if (my_strcmp(parsing->argv[parsing->index + 1], "true") == 0)
        server->game.game_settings.auto_end = true;
    else if (my_strcmp(parsing->argv[parsing->index + 1], "false") == 0)
        server->game.game_settings.auto_end = false;
    else
        EXCEPTION("Invalid argument for -e (or --autoEnd) option, "
            "it must be 'true' or 'false'");
    parsing->index += 1;
}
