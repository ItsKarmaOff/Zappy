/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The ppo.c
*/
/**
 * @file ppo.c
 * @brief The ppo.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_ppo_to_gui(server_t *server, client_t *client,
    player_t *player)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "ppo #%zu %zu %zu %i\n",
            player->id, player->position.x, player->position.y,
            player->orientation);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui)
            dprintf(server->client_list[index]->socket_fd,
                "ppo #%zu %zu %zu %i\n",
                player->id, player->position.x, player->position.y,
                player->orientation);
    }
}
