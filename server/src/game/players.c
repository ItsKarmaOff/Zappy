/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the players management functions
*/
/**
 * @file players.c
 * @brief The file containing the players management functions
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
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
    player->level = 1;
    player->inventory[FOOD] = DEFAULT_FOOD_NUMBER;
    player->last_eat_time = my_get_time();
    AL(FALSE, my_push_back, &game->map[player->position.y][player->position.x]
        .player_list, player, UNKNOWN);
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
    player->level = 1;
    player->inventory[FOOD] = DEFAULT_FOOD_NUMBER;
    player->last_eat_time = my_get_time();
    AL(FALSE, my_push_back, &game->map[player->position.y][player->position.x]
        .player_list, player, UNKNOWN);
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

static void player_eat(
    server_t *server, player_t *player, node_t **dead_players)
{
    if (player->inventory[FOOD] == 0) {
        DEBUG(my_create_str("Player %zu died", player->id));
        dprintf(player->client->socket_fd, DEATH_MESSAGE);
        send_pdi_to_gui(server, NULL, player);
        for (node_t *tmp = ACCESS_MAP(server->game.map, player)
        .incantation_list; tmp != NULL; tmp = tmp->next)
            my_delete_nodes((node_t **)&tmp->data, player, NULL);
        my_delete_nodes(&ACCESS_MAP(server->game.map, player).player_list,
            player, NULL);
        AL(FALSE, my_push_front, dead_players, player, UNKNOWN);
        player->client->player = NULL;
        remove_client(server, get_client_index(server, player->client));
    } else {
        player->inventory[FOOD]--;
        send_pin_to_gui(server, NULL, player);
    }
    player->last_eat_time = my_get_time();
}

void update_player(server_t *server, player_t *player, node_t **dead_players)
{
    if (server == NULL || player == NULL || player->is_egg)
        return;
    if (server->game.game_settings.is_paused == true) {
        player->last_eat_time = my_get_time();
        return;
    }
    if (server->game.game_settings.infinite_food == false
    && my_difftime(my_get_time(), player->last_eat_time) >=
    FOOD_TIME_UNIT / (double)server->game.game_settings.frequency)
        player_eat(server, player, dead_players);
}
