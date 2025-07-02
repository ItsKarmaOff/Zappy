/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "forward" command for AI clients
*/
/**
 * @file forward.c
 * @brief The file containing the handling of
 * the "forward" command for AI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_ai.h"

static void move_north(const game_t *game, player_t *player)
{
    player->position.y = (player->position.y == 0) ?
        game->game_settings.height - 1 : player->position.y - 1;
}

static void move_east(const game_t *game, player_t *player)
{
    player->position.x = (player->position.x ==
        game->game_settings.width - 1) ? 0 : player->position.x + 1;
}

static void move_south(const game_t *game, player_t *player)
{
    player->position.y = (player->position.y ==
        game->game_settings.height - 1) ? 0 : player->position.y + 1;
}

static void move_west(const game_t *game, player_t *player)
{
    player->position.x = (player->position.x == 0) ?
        game->game_settings.width - 1 : player->position.x - 1;
}

void handle_ai_command_forward(
    server_t *server, client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Forward\" command");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    my_delete_nodes(&ACCESS_MAP(server->game.map,
        client->player).player_list, client->player, NULL);
    moves[client->player->orientation - 1].
        move_func(&server->game, client->player);
    AL(FALSE, my_push_back, &ACCESS_MAP(server->game.map, client->player)
        .player_list, client->player, UNKNOWN);
    dprintf(client->socket_fd, VALID_AI);
    send_ppo_to_gui(server, NULL, client->player);
}

const move_t moves[] = {
    {NORTH, &move_north},
    {EAST, &move_east},
    {SOUTH, &move_south},
    {WEST, &move_west},
};
