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
    player->team = team;
    player->orientation = rand() % 4 + 1;
    return player;
}
