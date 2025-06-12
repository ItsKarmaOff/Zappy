/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The sst.c
*/
/**
 * @file sst.c
 * @brief The sst.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void send_sst_to_gui(server_t *server, client_t *client)
{
    if (server == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "sst %zu\n",
            server->game.game_settings.frequency);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd, "sst %zu\n",
                server->game.game_settings.frequency);
    }
}
