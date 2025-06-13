/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The add_new_client.c
*/
/**
 * @file add_new_client.c
 * @brief The add_new_client.c
 * @author Nicolas TORO
 */

#include "network.h"

static void add_client_to_server(server_t *server, client_t *new_client)
{
    resize_client_list(server, server->current_clients_number + 1);
    server->poll_fds[server->current_clients_number].fd =
        new_client->socket_fd;
    server->poll_fds[server->current_clients_number].events = POLLIN;
    server->client_list[server->current_clients_number - 1] = new_client;
    DEBUG(my_create_str("New client added at index %zu\n",
        server->current_clients_number - 1));
}

void add_new_client(server_t *server)
{
    client_t *new_client = AL(FALSE, my_calloc, 1, sizeof(client_t));
    socklen_t client_size = sizeof(new_client->address);

    new_client->socket_fd = accept(server->socket_fd,
        (struct sockaddr *)&new_client->address, &client_size);
    if (new_client->socket_fd == -1) {
        FREE(new_client);
        THROW(my_create_str("EXCEPTION: accept client: %s\n", STRERR));
    }
    dprintf(new_client->socket_fd, WELCOME_MESSAGE);
    add_client_to_server(server, new_client);
}
