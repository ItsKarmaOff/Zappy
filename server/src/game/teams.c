/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The teams.c
*/
/**
 * @file teams.c
 * @brief The teams.c
 * @author Nicolas TORO
 */

#include "game.h"

team_t *create_team(game_t *game, const char *name)
{
    team_t *team = my_calloc(1, sizeof(team_t));
    player_t *new_player = NULL;

    team->name = name;
    if (my_strcmp(name, GRAPHIC_TEAM_NAME) == 0)
        return team;
    team->eggs_number = game->game_settings.start_clients_per_team;
    for (size_t index = 0; index < team->eggs_number; index++) {
        new_player = create_player(game, team);
        AL(FALSE, my_push_back, &team->player_list, new_player, VOID);
    }
    return team;
}

size_t get_team_index(const game_t *game, const char *team_name)
{
    if (game == NULL || team_name == NULL)
        return 0;
    for (size_t index = 0; index < game->game_settings.teams_number; index++) {
        if (my_strcmp(game->team_list[index]->name, team_name) == 0)
            return index;
    }
    return 0;
}

player_t *get_next_egg(server_t *server, team_t *team)
{
    if (team == NULL || my_strcmp(team->name, GRAPHIC_TEAM_NAME) == 0)
        return NULL;
    for (node_t *node = team->player_list; node != NULL; node = node->next) {
        if (node->data != NULL && ((player_t *)node->data)->is_egg) {
            ((player_t *)node->data)->is_egg = false;
            team->eggs_number--;
            send_ebo_to_gui(server, NULL, (player_t *)node->data);
            send_pnw_to_gui(server, NULL, (player_t *)node->data);
            send_pin_to_gui(server, NULL, (player_t *)node->data);
            return (player_t *) node->data;
        }
    }
    return NULL;
}

bool is_valid_team(server_t *server, char *team_name)
{
    for (size_t index = 0; index < server->game.game_settings.teams_number;
        index++) {
        if (my_strcmp(team_name, server->game.team_list[index]->name) == 0)
            return true;
    }
    return false;
}
