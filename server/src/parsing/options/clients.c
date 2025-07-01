/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "clients" option
*/
/**
 * @file clients.c
 * @brief The file containing the function for the "clients" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void option_clients(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -c (or --clients) option");
    server->game.game_settings.start_clients_per_team =
        my_get_number(parsing->argv[parsing->index + 1], DEFAULT_NB);
    if (my_errno != SUCCESS ||
    server->game.game_settings.start_clients_per_team <= 0)
        EXCEPTION("Invalid argument for -c (or --clients) option, "
            "it must be a number greater than 0");
    parsing->index += 1;
}
