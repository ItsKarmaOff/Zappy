/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The smg.c
*/
/**
 * @file smg.c
 * @brief The smg.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_smg_to_gui(server_t *server, client_t *client,
    const char *message)
{
    if (server == NULL || message == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "smg %s\n", message);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "smg %s\n", message);
    }
}
