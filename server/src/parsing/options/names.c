/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The names.c
*/
/**
 * @file names.c
 * @brief The names.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void add_teams(server_t *server, char **argv,
    const size_t *index, size_t name_index)
{
    server->game.game_settings.teams_number = name_index - *index - 1;
    server->game.team_list = my_calloc(
        name_index - *index + 1, sizeof(team_t *));
    server->game.team_list[0] = create_team(GRAPHIC_TEAM_NAME);
    for (size_t new_index = *index + 1; new_index < name_index; new_index++) {
        if (argv[new_index][0] == '-')
            break;
        server->game.team_list[new_index - *index] =
            create_team(argv[new_index]);
    }
}

void option_names(server_t *server,
    int argc, char **argv, size_t *index)
{
    size_t name_index = *index + 1;

    if ((size_t)argc < *index + 1)
        EXCEPTION("Missing argument for -n (or --names) option\n");
    for (; name_index < (size_t)argc; name_index++) {
        if (argv[name_index][0] == '-')
            break;
    }
    if (name_index - *index < 2)
        EXCEPTION("At least two team names are required "
            "for -n (or --names) option\n");
    add_teams(server, argv, index, name_index);
    *index = name_index - 1;
}
