/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The pdr.c
*/
/**
 * @file pdr.c
 * @brief The pdr.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void send_pdr_to_gui(server_t *server, client_t *client,
    player_t *player, resources_t resource_id)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "pdr #%zu %i\n",
            player->id, resource_id);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "pdr #%zu %i\n", player->id, resource_id);
    }
}
