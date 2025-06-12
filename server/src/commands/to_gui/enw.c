/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The enw.c
*/
/**
 * @file enw.c
 * @brief The enw.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void send_enw_to_gui(server_t *server, client_t *client,
    player_t *egg)
{
    if (server == NULL || egg == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "enw #%zu #%zi %zu %zu\n",
            egg->id, (egg->creator_id == 0) ? -1 : (ssize_t)egg->creator_id,
            egg->position.x, egg->position.y);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "enw #%zu #%zi %zu %zu\n",
                egg->id,
                (egg->creator_id == 0) ? -1 : (ssize_t)egg->creator_id,
                egg->position.x, egg->position.y);
    }
}
