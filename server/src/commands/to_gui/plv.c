/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "plv" command for GUI clients
*/
/**
 * @file plv.c
 * @brief The file containing the sending of
 * the "plv" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void send_plv_to_gui(server_t *server, client_t *client,
    player_t *player)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "plv #%zu %zu\n",
            player->id, player->level);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "plv #%zu %zu\n",
                player->id, player->level);
    }
}
