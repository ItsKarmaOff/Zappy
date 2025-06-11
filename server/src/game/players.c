/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The players.c
*/
/**
 * @file players.c
 * @brief The players.c
 * @author Nicolas TORO
 */

#include "game.h"

player_t *create_player(game_t *game, team_t *team)
{
    player_t *player = AL(FALSE, my_calloc, 1, sizeof(player_t));

    player->id = game->game_settings.next_player_id;
    game->game_settings.next_player_id++;
    player->is_egg = true;
    player->team = team;
    player->position.x = rand() % game->game_settings.width;
    player->position.y = rand() % game->game_settings.height;
    player->orientation = rand() % 4 + 1;
    player->inventory[FOOD] = DEFAULT_FOOD_NUMBER;
    player->last_eat_time = time(NULL);
    return player;
}

player_t *create_player_from_player(game_t *game, player_t *creator)
{
    player_t *player = AL(FALSE, my_calloc, 1, sizeof(player_t));

    player->id = game->game_settings.next_player_id;
    game->game_settings.next_player_id++;
    player->team = creator->team;
    player->is_egg = true;
    player->team->eggs_number++;
    player->creator_id = creator->id;
    player->position = creator->position;
    player->orientation = creator->orientation;
    player->inventory[FOOD] = DEFAULT_FOOD_NUMBER;
    player->last_eat_time = time(NULL);
    return player;
}

static player_t *get_player_in_team_by_id(const team_t *team, size_t player_id)
{
    if (team == NULL)
        return NULL;
    for (node_t *node = team->player_list; node != NULL;
        node = node->next) {
        if (node->data != NULL && ((player_t *)node->data)->id == player_id)
            return (player_t *)node->data;
    }
    return NULL;
}

player_t *get_player_by_id(const game_t *game, size_t player_id)
{
    player_t *player = NULL;

    if (game == NULL || player_id >= game->game_settings.next_player_id)
        return NULL;
    for (size_t index = 0; index < game->game_settings.teams_number; index++) {
        player = get_player_in_team_by_id(game->team_list[index], player_id);
        if (player != NULL)
            return player;
    }
    return NULL;
}
