/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The show_eggs.c
*/
/**
 * @file show_eggs.c
 * @brief The show_eggs.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_show_eggs(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -s (or --showEggs) option\n");
    my_strlowcase(parsing->argv[parsing->index + 1]);
    if (my_strcmp(parsing->argv[parsing->index + 1], "true") == 0)
        server->game.game_settings.show_eggs = true;
    else if (my_strcmp(parsing->argv[parsing->index + 1], "false") == 0)
        server->game.game_settings.show_eggs = false;
    else
        EXCEPTION("Invalid argument for -s (or --showEggs) option, "
            "it must be 'true' or 'false'\n");
    parsing->index += 1;
}
