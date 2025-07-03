/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "ebo" command for GUI clients
*/
/**
 * @file ebo.c
 * @brief The file containing the sending of
 * the "ebo" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void send_ebo_to_gui(server_t *server, client_t *client,
    player_t *egg)
{
    if (server == NULL || egg == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "ebo #%zu\n", egg->id);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "ebo #%zu\n", egg->id);
    }
}
