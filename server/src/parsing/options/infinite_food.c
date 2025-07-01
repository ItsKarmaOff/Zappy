/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "infinite_food" option
*/
/**
 * @file infinite_food.c
 * @brief The file containing the function for the "infinite_food" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void option_infinite_food(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -i (or --infiniteFood) option");
    my_strlowcase(parsing->argv[parsing->index + 1]);
    if (my_strcmp(parsing->argv[parsing->index + 1], "true") == 0)
        server->game.game_settings.infinite_food = true;
    else if (my_strcmp(parsing->argv[parsing->index + 1], "false") == 0)
        server->game.game_settings.infinite_food = false;
    else
        EXCEPTION("Invalid argument for -i (or --infiniteFood) option, "
            "it must be 'true' or 'false'");
    parsing->index += 1;
}
