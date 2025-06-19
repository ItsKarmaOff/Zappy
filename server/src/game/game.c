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

    DEBUG(LIGHT_GREY "Refilling resources...\n");
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

static void disconnect_player(server_t *server, player_t *player)
{
    if (player != NULL && !player->is_egg && player->client != NULL) {
        my_dprintf(player->client->socket_fd,
            "%s\n", server->game.winner_team_name);
        player->client->player = NULL;
        remove_client(server, get_client_index(server, player->client));
        player->client = NULL;
    }
}

static void set_winner_team(server_t *server, const char *team_name)
{
    server->game.winner_team_name = team_name;
    DEBUG(my_create_str(GREEN "The winner team is: %s\n", team_name));
    send_seg_to_gui(server, NULL);
    for (size_t index = 0; index < server->game.game_settings.teams_number;
    index++) {
        for (node_t *node = server->game.team_list[index]->player_list;
        node != NULL; node = node->next)
            disconnect_player(server, (player_t *)node->data);
        my_delete_list(&server->game.team_list[index]->player_list);
    }
}

static void check_end_game(server_t *server)
{
    size_t teams_alive = 0;
    const char *tmp_winner_team_name = NULL;

    if (server->game.winner_team_name != NULL)
        return;
    for (size_t index = 0; index < server->game.game_settings.teams_number;
    index++) {
        if (server->game.team_list[index]->player_list != NULL) {
            teams_alive++;
            tmp_winner_team_name = server->game.team_list[index]->name;
        }
        if (get_number_of_player_level_max_in_team(server->game.
        team_list[index]) >= NUMBER_OF_PLAYER_LEVEL_MAX_TO_WIN) {
            set_winner_team(server, server->game.team_list[index]->name);
            return;
        }
    }
    if (server->game.game_settings.auto_end && teams_alive <= 1)
        set_winner_team(server, tmp_winner_team_name);
}

void update_game(UNUSED server_t *server)
{
    node_t *dead_players = NULL;

    if (difftime(time(NULL), server->game.last_refill_time) >=
    REFILL_TIME / (double)server->game.game_settings.frequency)
        refill_resources(&server->game);
    for (size_t index = 0; index < server->game.game_settings.teams_number;
    index++) {
        for (node_t *node = server->game.team_list[index]->player_list;
        node != NULL; node = node->next)
            update_player(server, (player_t *)node->data, &dead_players);
        for (node_t *node = dead_players; node != NULL; node = node->next)
            my_delete_nodes(&server->game.team_list[index]->player_list,
                (player_t *)node->data, NULL);
        my_delete_list(&dead_players);
    }
    check_end_game(server);
}
