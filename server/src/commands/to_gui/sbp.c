/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The sbp.c
*/
/**
 * @file sbp.c
 * @brief The sbp.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void send_sbp_to_gui(server_t *server, client_t *client)
{
    if (server == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "sbp\n");
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd, "sbp\n");
    }
}
