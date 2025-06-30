/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "no_refill" option
*/
/**
 * @file no_refill.c
 * @brief The file containing the function for the "no_refill" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void option_no_refill(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -r (or --noRefill) option");
    my_strlowcase(parsing->argv[parsing->index + 1]);
    if (my_strcmp(parsing->argv[parsing->index + 1], "true") == 0)
        server->game.game_settings.no_refill = true;
    else if (my_strcmp(parsing->argv[parsing->index + 1], "false") == 0)
        server->game.game_settings.no_refill = false;
    else
        EXCEPTION("Invalid argument for -r (or --noRefill) option, "
            "it must be 'true' or 'false'");
    parsing->index += 1;
}
