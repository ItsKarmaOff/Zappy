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

#include "commands/gui.h"

void send_enw_to_gui(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED player_t *egg)
{
    if (server == NULL || egg == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "enw #%zu #%zu %zu %zu\n",
            egg->id, egg->creator_id, egg->position.x, egg->position.y);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui) {
            dprintf(server->client_list[index]->socket_fd,
                "enw #%zu #%zu %zu %zu\n",
                egg->id, egg->creator_id, egg->position.x, egg->position.y);
        }
    }
}
