/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "pbc" command for GUI clients
*/
/**
 * @file pbc.c
 * @brief The file containing the sending of
 * the "pbc" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void send_pbc_to_gui(server_t *server, client_t *client,
    player_t *player, const char *message)
{
    if (server == NULL || message == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "pbc #%zi %s\n",
            ((player == NULL) ? -1 : (ssize_t)player->id), message);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "pbc #%zi %s\n",
                ((player == NULL) ? -1 : (ssize_t)player->id), message);
    }
}
