/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "frequency" option
*/
/**
 * @file frequency.c
 * @brief The file containing the function for the "frequency" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void option_frequency(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -f (or --frequency) option");
    server->game.game_settings.frequency =
        my_get_number(parsing->argv[parsing->index + 1], DEFAULT_NB);
    if (my_errno != SUCCESS || server->game.game_settings.frequency <= 0)
        EXCEPTION("Invalid argument for -f (or --frequency) option, "
            "it must be a number greater than 0");
    parsing->index += 1;
}
