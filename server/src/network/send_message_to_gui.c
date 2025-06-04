/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The send_message_to_gui.c
*/
/**
 * @file send_message_to_gui.c
 * @brief The send_message_to_gui.c
 * @author Nicolas TORO
 */

#include "network.h"

void send_message_to_gui(server_t *server, const char *message)
{
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui) {
            dprintf(server->client_list[index]->socket_fd, "%s", message);
        }
    }
}