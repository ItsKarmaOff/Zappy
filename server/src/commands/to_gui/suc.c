/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The suc.c
*/
/**
 * @file suc.c
 * @brief The suc.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_suc_to_gui(UNUSED server_t *server, UNUSED client_t *client)
{
    if (server == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "suc\n");
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui)
            dprintf(server->client_list[index]->socket_fd, "suc\n");
    }
}
