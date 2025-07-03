/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function to send a message to GUI clients
*/
/**
 * @file send_message_to_gui.c
 * @brief The file containing the function to send a message to GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "network.h"

void send_message_to_gui(server_t *server, const char *message)
{
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd, "%s", message);
    }
}
