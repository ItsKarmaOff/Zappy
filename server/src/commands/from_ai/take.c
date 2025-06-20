/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The take.c
*/
/**
 * @file take.c
 * @brief The take.c
 * @author Nicolas TORO
 */

#include "commands/commands_ai.h"

static void take_resource(
    server_t *server, client_t *client, resources_t resource_id)
{
    dprintf(client->socket_fd, VALID_AI);
    ACCESS_MAP(server->game.map, client->player).resources[resource_id]--;
    client->player->inventory[resource_id]++;
    server->game.resources[resource_id].current_quantity--;
    send_pgt_to_gui(server, NULL, client->player, resource_id);
}

void handle_ai_command_take(
    server_t *server, client_t *client, char **args)
{
    size_t resource_id = 0;

    DEBUG("Executing \"Take\" command");
    if (my_array_len((void **) args) != 2) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    for (; resource_id < RESOURCES_SIZE; resource_id++) {
        if (strcmp(args[1], resources_names[resource_id]) == 0)
            break;
    }
    if (resource_id == RESOURCES_SIZE ||
    ACCESS_MAP(server->game.map, client->player).resources[resource_id] == 0)
        dprintf(client->socket_fd, WRONG_AI);
    else
        take_resource(server, client, resource_id);
}
