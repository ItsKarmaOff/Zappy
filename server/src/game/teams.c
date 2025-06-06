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
        AL(FALSE, my_push_front, &team->player_list, new_player, VOID);
    }
    return team;
}

//TODO à delete
// Plus utilisé à cause de eggs_number
/*
size_t get_nb_empty_slots(const team_t *team)
{
    size_t empty_slots = 0;

    if (team == NULL)
        return empty_slots;
    for (node_t *node = team->player_list; node != NULL; node = node->next) {
        if (node->data == NULL || ((player_t *)node->data)->is_egg)
            empty_slots++;
    }
    return empty_slots;
}*/
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

player_t *get_next_egg(team_t *team)
{
    if (team == NULL || my_strcmp(team->name, GRAPHIC_TEAM_NAME) == 0)
        return NULL;
    for (node_t *node = team->player_list; node != NULL; node = node->next) {
        if (node->data != NULL && ((player_t *)node->data)->is_egg) {
            ((player_t *)node->data)->is_egg = false;
            team->eggs_number--;
            return (player_t *) node->data;
        }
    }
    return NULL;
}
