/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The start_server.c
*/
/**
 * @file start_server.c
 * @brief The start_server.c
 * @author Nicolas TORO
 */

#include "network.h"

static void configure_server(server_t *server)
{
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    server->poll_fds = AL(FALSE, my_calloc, 1, sizeof(pollfd_t));
    server->poll_fds[SERVER_POLL_INDEX].fd = -1;
    server->poll_fds[SERVER_POLL_INDEX].events = POLLIN;
}

void start_server(server_t *server)
{
    configure_server(server);
    server->socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server->socket_fd < 0)
        THROW(my_create_str("EXCEPTION: "
            "Socket creation failed: %s\n", STRERR));
    my_add_to_garbage(true, &server->socket_fd, &my_close);
    server->poll_fds[SERVER_POLL_INDEX].fd = server->socket_fd;
    if (bind(server->socket_fd, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0)
        THROW(my_create_str("EXCEPTION: Bind failed: %s\n", STRERR));
    if (listen(server->socket_fd, DEFAULT_LISTEN_BACKLOG) < 0)
        THROW(my_create_str("EXCEPTION: Listen failed: %s\n", STRERR));
}
