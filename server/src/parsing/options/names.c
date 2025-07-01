/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "names" option
*/
/**
 * @file names.c
 * @brief The file containing the function for the "names" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void add_teams(server_t *server, parsing_t *parsing, size_t name_index)
{
    server->game.game_settings.teams_number = name_index - parsing->index;
    server->game.team_list = my_calloc(
        name_index - parsing->index + 1, sizeof(team_t *));
    my_push_front(&parsing->team_name_list,
        GRAPHIC_TEAM_NAME, UNKNOWN);
    for (size_t new_index = parsing->index + 1;
    new_index < name_index; new_index++) {
        if (parsing->argv[new_index][0] == '-')
            break;
        my_push_back(&parsing->team_name_list,
            parsing->argv[new_index], UNKNOWN);
    }
}

void option_names(server_t *server, parsing_t *parsing)
{
    size_t name_index = parsing->index + 1;

    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -n (or --names) option");
    for (; name_index < parsing->argc; name_index++) {
        if (parsing->argv[name_index][0] == '-')
            break;
    }
    if (name_index - parsing->index < 2)
        EXCEPTION("At least two team names are required "
            "for -n (or --names) option");
    add_teams(server, parsing, name_index);
    parsing->index = name_index - 1;
}
