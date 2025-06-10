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

#include "commands/gui.h"

void send_msz_to_gui(server_t *server, UNUSED client_t *client)
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
        if (server->client_list[index]->is_gui) {
            dprintf(server->client_list[index]->socket_fd,
                "msz %zu %zu\n",
                server->game.game_settings.width,
                server->game.game_settings.height);
        }
    }
}
