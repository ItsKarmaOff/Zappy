/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The edi.c
*/
/**
 * @file edi.c
 * @brief The edi.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_edi_to_gui(server_t *server, client_t *client,
    player_t *egg)
{
    if (server == NULL || egg == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "edi #%zu\n", egg->id);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "edi #%zu\n", egg->id);
    }
}
