/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "set" command for AI clients
*/
/**
 * @file set.c
 * @brief The file containing the handling of
 * the "set" command for AI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_ai.h"

static void set_resource(
    server_t *server, client_t *client, resources_t resource_id)
{
    dprintf(client->socket_fd, VALID_AI);
    client->player->inventory[resource_id]--;
    ACCESS_MAP(server->game.map, client->player).resources[resource_id]++;
    server->game.resources[resource_id].current_quantity++;
    send_pdr_to_gui(server, NULL, client->player, resource_id);
}

void handle_ai_command_set(
    server_t *server, client_t *client, char **args)
{
    size_t resource_id = 0;

    DEBUG("Executing \"Set\" command");
    if (my_array_len((void **) args) != 2) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    for (; resource_id < RESOURCES_SIZE; resource_id++) {
        if (strcmp(args[1], resources_names[resource_id]) == 0)
            break;
    }
    if (resource_id == RESOURCES_SIZE ||
    client->player->inventory[resource_id] == 0)
        dprintf(client->socket_fd, WRONG_AI);
    else
        set_resource(server, client, resource_id);
}
