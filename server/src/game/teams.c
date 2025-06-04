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

team_t *create_team(const char *name)
{
    team_t *team = my_calloc(1, sizeof(team_t));

    team->name = name;
    return team;
}

size_t get_nb_players_in_team(const game_t *game, const team_t *team)
{
    size_t count = 0;

    if (team == NULL || team->player_list == NULL)
        return count;
    for (size_t index = 0; index < game->game_settings.clients_per_team;
    index++) {
        if (team->player_list[index] != NULL)
            count++;
    }
    return count;
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
