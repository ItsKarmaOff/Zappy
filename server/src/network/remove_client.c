/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function to remove a client
*/
/**
 * @file remove_client.c
 * @brief The file containing the function to remove a client
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "network.h"

void remove_client(server_t *server, size_t index)
{
    if (server == NULL || index == 0)
        return;
    DEBUG(my_create_str("Removing client at index %zu", index - 1));
    close(server->poll_fds[index].fd);
    destroy_client(server, server->client_list[index - 1], false);
    if (server->current_clients_number == 1) {
        server->client_list[index - 1] = NULL;
        server->poll_fds[index].fd = -1;
        server->poll_fds[index].events = POLLIN;
        server->poll_fds[index].revents = 0;
    } else {
        server->poll_fds[index] =
            server->poll_fds[server->current_clients_number];
        server->client_list[index - 1] =
            server->client_list[server->current_clients_number - 1];
    }
    resize_client_list(server, server->current_clients_number - 1);
}
