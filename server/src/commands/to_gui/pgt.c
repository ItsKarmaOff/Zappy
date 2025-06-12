/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The pgt.c
*/
/**
 * @file pgt.c
 * @brief The pgt.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_pgt_to_gui(server_t *server, client_t *client,
    player_t *player, resources_t resource_id)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "pgt #%zu %i\n",
            player->id, resource_id);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "pgt #%zu %i\n", player->id, resource_id);
    }
}
