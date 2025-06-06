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
    return player;
}
