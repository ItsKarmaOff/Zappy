/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The forward.c
*/
/**
 * @file forward.c
 * @brief The forward.c
 * @author Nicolas TORO
 */

#include "commands/ai.h"

static void move_north(server_t *server, client_t *client)
{
    client->player->position.y = (client->player->position.y == 0) ?
        server->game.game_settings.height - 1 :
        client->player->position.y - 1;
}

static void move_east(server_t *server, client_t *client)
{
    client->player->position.x = (client->player->position.x ==
        server->game.game_settings.width - 1) ? 0 :
        client->player->position.x + 1;
}

static void move_south(server_t *server, client_t *client)
{
    client->player->position.y = (client->player->position.y ==
        server->game.game_settings.height - 1) ? 0 :
        client->player->position.y + 1;
}

static void move_west(server_t *server, client_t *client)
{
    client->player->position.x = (client->player->position.x == 0) ?
        server->game.game_settings.width - 1 :
        client->player->position.x - 1;
}

void handle_command_forward(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED char **args)
{
    DEBUG("Executing \"Forward\" command\n");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    moves[client->player->orientation - 1].move_func(server, client);
    dprintf(client->socket_fd, VALID_AI);
    client->time_to_wait = 7;
}

const move_t moves[] = {
    {NORTH, &move_north},
    {EAST, &move_east},
    {SOUTH, &move_south},
    {WEST, &move_west},
};
