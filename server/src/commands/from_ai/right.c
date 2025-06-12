/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The right.c
*/
/**
 * @file right.c
 * @brief The right.c
 * @author Nicolas TORO
 */

#include "commands/commands_ai.h"

static void update_orientation_north(client_t *client)
{
    client->player->orientation = EAST;
}

static void update_orientation_east(client_t *client)
{
    client->player->orientation = SOUTH;
}

static void update_orientation_south(client_t *client)
{
    client->player->orientation = WEST;
}

static void update_orientation_west(client_t *client)
{
    client->player->orientation = NORTH;
}

void handle_command_right(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED char **args)
{
    static const update_orientation_t update_orientation[] = {
        {NORTH, &update_orientation_north},
        {EAST, &update_orientation_east},
        {SOUTH, &update_orientation_south},
        {WEST, &update_orientation_west},
    };

    DEBUG("Executing \"Right\" command\n");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    update_orientation[client->player->orientation - 1].
        update_orientation_func(client);
    dprintf(client->socket_fd, VALID_AI);
    send_ppo_to_gui(server, NULL, client->player);
}
