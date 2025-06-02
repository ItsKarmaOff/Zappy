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

static void analyse_name(server_t *server,
    char **argv, size_t name_index, node_t **teams_names)
{
    if (my_strcmp(argv[name_index], GRAPHIC_TEAM_NAME) == 0) {
        my_delete_list(teams_names);
        EXCEPTION("The team name \"" GRAPHIC_TEAM_NAME
            "\" is reserved for the graphic client\n");
    }
    if (my_find_node(*teams_names, argv[name_index], &my_strcmp) != NULL) {
        my_delete_list(teams_names);
        THROW(my_create_str("EXCEPTION: The team name \"%s\" "
            "is already used\n", argv[name_index]));
    }
    my_push_back(&server->game.team_list,
        create_team(argv[name_index]), UNKNOWN);
    AL(FALSE, my_push_front, teams_names, argv[name_index], UNKNOWN);
}

void option_names(server_t *server,
    int argc, char **argv, size_t *index)
{
    node_t *teams_names = NULL;

    if ((size_t)argc < *index + 1)
        EXCEPTION("Missing argument for -n (or --names) option\n");
    AL(FALSE, my_push_front, &teams_names, GRAPHIC_TEAM_NAME, UNKNOWN);
    for (size_t name_index = *index + 1;
    name_index < (size_t)argc; name_index++) {
        if (argv[name_index][0] == '-')
            break;
        analyse_name(server, argv, name_index, &teams_names);
        *index += 1;
    }
    my_delete_list(&teams_names);
    if (my_list_size(server->game.team_list) == 0)
        EXCEPTION("No team names provided, "
            "at least one team name is required\n");
}
