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

void refill_resources(game_t *game)
{
    size_t x = 0;
    size_t y = 0;

    DEBUG("Refilling resources...\n");
    for (size_t index = 0; index < RESOURCES_SIZE; index++) {
        while (game->resources[index].current_quantity <
        game->resources[index].max_quantity) {
            x = rand() % game->game_settings.width;
            y = rand() % game->game_settings.height;
            game->resources[index].current_quantity += ((
                game->map[y][x].resources[index] == 0) ? 1 : 0);
            game->map[y][x].resources[index] = 1;
        }
    }
    game->last_refill_time = time(NULL);
}

void create_game_map(game_t *game)
{
    game->map = my_calloc(1, sizeof(tile_t *) * game->game_settings.height);
    for (size_t y = 0; y < game->game_settings.height; y++) {
        game->map[y] = my_calloc(1, sizeof(tile_t) *
            game->game_settings.width);
        for (size_t x = 0; x < game->game_settings.width; x++) {
            game->map[y][x].position.x = x;
            game->map[y][x].position.y = y;
        }
    }
    for (size_t index = 0; index < RESOURCES_SIZE; index++) {
        game->resources[index].max_quantity =
            game->game_settings.width * game->game_settings.height
            * resources_densities[index];
    }
    refill_resources(game);
}

void update_game(UNUSED server_t *server)
{
    if (difftime(time(NULL), server->game.last_refill_time) >=
    REFILL_TIME / (double)server->game.game_settings.frequency)
        refill_resources(&server->game);
}
