/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The msz.c
*/
/**
 * @file msz.c
 * @brief The msz.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void send_msz_to_gui(server_t *server, client_t *client)
{
    if (server == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd,
            "msz %zu %zu\n",
            server->game.game_settings.width,
            server->game.game_settings.height);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "msz %zu %zu\n",
                server->game.game_settings.width,
                server->game.game_settings.height);
    }
}
