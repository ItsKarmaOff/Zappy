/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The seg.c
*/
/**
 * @file seg.c
 * @brief The seg.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_seg_to_gui(server_t *server, client_t *client,
    team_t *team)
{
    if (server == NULL || team == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "seg %s\n", team->name);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui) {
            dprintf(server->client_list[index]->socket_fd, "seg %s\n",
                team->name);
        }
    }
}
