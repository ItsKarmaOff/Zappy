/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The display_eggs.c
*/
/**
 * @file display_eggs.c
 * @brief The display_eggs.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_display_eggs(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -d (or --displayEggs) option\n");
    my_strlowcase(parsing->argv[parsing->index + 1]);
    if (my_strcmp(parsing->argv[parsing->index + 1], "true") == 0)
        server->game.game_settings.display_eggs = true;
    else if (my_strcmp(parsing->argv[parsing->index + 1], "false") == 0)
        server->game.game_settings.display_eggs = false;
    else
        EXCEPTION("Invalid argument for -d (or --displayEggs) option, "
            "it must be 'true' or 'false'\n");
    parsing->index += 1;
}