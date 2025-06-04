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

player_t *create_player(team_t *team)
{
    player_t *player = my_calloc(1, sizeof(player_t));

    player->team = team;
    player->orientation = rand() % 4 + 1;
    return player;
}
