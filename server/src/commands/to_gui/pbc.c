/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The pbc.c
*/
/**
 * @file pbc.c
 * @brief The pbc.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_pbc_to_gui(server_t *server, client_t *client,
    player_t *player, const char *message)
{
    if (server == NULL || player == NULL || message == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "pbc #%zu %s\n", player->id, message);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui)
            dprintf(server->client_list[index]->socket_fd,
                "pbc #%zu %s\n", player->id, message);
    }
}
