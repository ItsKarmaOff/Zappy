/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The game.c
*/
/**
 * @file game.c
 * @brief The game.c
 * @author Nicolas TORO
 */

#include "game.h"

void destroy_game(game_t *game)
{
    for (size_t index = 0; index < game->game_settings.teams_number; index++) {
        my_delete_list(&game->team_list[index]->player_list);
    }
    game->game_settings.teams_number = 0;
}

void update_game(UNUSED server_t *server)
{
    return;
}
