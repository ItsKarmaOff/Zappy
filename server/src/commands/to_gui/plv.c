/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The plv.c
*/
/**
 * @file plv.c
 * @brief The plv.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_plv_to_gui(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED player_t *player, UNUSED size_t level)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "plv #%zu %zu\n", player->id, level);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui)
            dprintf(server->client_list[index]->socket_fd,
                "plv #%zu %zu\n", player->id, level);
    }
}
