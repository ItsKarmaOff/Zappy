/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "suc" command for GUI clients
*/
/**
 * @file suc.c
 * @brief The file containing the sending of
 * the "suc" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void send_suc_to_gui(UNUSED server_t *server, UNUSED client_t *client)
{
    if (server == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "suc\n");
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd, "suc\n");
    }
}
