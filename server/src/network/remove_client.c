/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The remove_client.c
*/
/**
 * @file remove_client.c
 * @brief The remove_client.c
 * @author Nicolas TORO
 */

#include "network.h"

void remove_client(server_t *server, size_t index)
{
    DEBUG(my_create_str("Removing client at index %zu\n", index));
    close(server->poll_fds[index].fd);
    if (server->current_clients_number == 1) {
        server->poll_fds[index].fd = -1;
        destroy_client(server->client_list[index - 1]);
        server->client_list[index - 1] = NULL;
    } else {
        server->poll_fds[index] =
            server->poll_fds[server->current_clients_number];
        server->client_list[index - 1] =
            server->client_list[server->current_clients_number - 1];
        server->poll_fds[server->current_clients_number].fd = -1;
        server->client_list[server->current_clients_number - 1] = NULL;
    }
    my_resize_alloc(server->poll_fds,
        sizeof(pollfd_t) * (server->max_clients_number + 1),
        sizeof(pollfd_t) * server->max_clients_number);
    my_resize_alloc(server->client_list,
        sizeof(client_t *) * (server->max_clients_number),
        sizeof(client_t *) * (server->max_clients_number - 1));
    server->current_clients_number--;
}
