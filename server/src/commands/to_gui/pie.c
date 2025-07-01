/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "pie" command for GUI clients
*/
/**
 * @file pie.c
 * @brief The file containing the sending of
 * the "pie" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void send_pie_to_gui(server_t *server, client_t *client,
    vector2u_t position, bool incantation_result)
{
    if (server == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "pie %zu %zu %d\n",
            position.x, position.y, incantation_result);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd, "pie %zu %zu %d\n",
                position.x, position.y, incantation_result);
    }
}
