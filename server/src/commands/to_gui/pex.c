/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "pex" command for GUI clients
*/
/**
 * @file pex.c
 * @brief The file containing the sending of
 * the "pex" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void send_pex_to_gui(server_t *server, client_t *client,
    player_t *player)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "pex #%zu\n", player->id);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd, "pex #%zu\n",
                player->id);
    }
}
