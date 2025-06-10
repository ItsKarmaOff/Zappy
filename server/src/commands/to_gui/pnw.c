/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The pnw.c
*/
/**
 * @file pnw.c
 * @brief The pnw.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_pnw_to_gui(server_t *server, client_t *client,
    player_t *player)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "pnw #%zu %zu %zu %i %zu %s\n",
            player->id, player->position.x, player->position.y,
            player->orientation, player->level, player->team->name);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui)
            dprintf(server->client_list[index]->socket_fd,
                "pnw #%zu %zu %zu %i %zu %s\n",
                player->id, player->position.x, player->position.y,
                player->orientation, player->level, player->team->name);
    }
}
