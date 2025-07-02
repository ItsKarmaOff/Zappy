/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "auto_end" option
*/
/**
 * @file auto_end.c
 * @brief The file containing the function for the "auto_end" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
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
