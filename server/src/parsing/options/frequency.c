/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The frequency.c
*/
/**
 * @file frequency.c
 * @brief The frequency.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_frequency(server_t *server,
    int argc, char **argv, size_t *index)
{
    if ((size_t)argc < *index + 1)
        EXCEPTION("Missing argument for -f (or --frequency) option\n");
    server->game.game_settings.frequency =
        my_get_number(argv[*index + 1], DEFAULT_NB);
    if (my_errno != SUCCESS || server->game.game_settings.frequency <= 0)
        EXCEPTION("Invalid argument for -f (or --frequency) option, "
            "it must be a number greater than 0\n");
    *index += 1;
}
