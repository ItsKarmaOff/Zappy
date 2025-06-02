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
    server->max_clients_number = server->game.game_settings.clients_per_team *
        my_list_size(server->game.team_list);
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(server->port);
    server->poll_fds = my_calloc(
        server->max_clients_number + 1, sizeof(struct pollfd));
    for (size_t index = 0; index < server->max_clients_number + 1; index++) {
        server->poll_fds[index].fd = -1;
        server->poll_fds[index].events = POLLIN;
    }
    server->client_list = my_calloc(
        server->max_clients_number, sizeof(client_t *));
}

void start_server(server_t *server)
{
    configure_server(server);
    server->socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server->socket_fd < 0)
        THROW(my_create_str("EXCEPTION: "
            "Socket creation failed: ", strerror(errno)));
    my_add_to_garbage(true, &server->socket_fd, &my_close);
    server->poll_fds[0].fd = server->socket_fd;
    if (bind(server->socket_fd, (struct sockaddr *)&server->address,
    sizeof(server->address)) < 0)
        THROW(my_create_str("EXCEPTION: "
            "Bind failed: ", strerror(errno)));
    if (listen(server->socket_fd, (int)server->max_clients_number) < 0)
        THROW(my_create_str("EXCEPTION: "
            "Listen failed: ", strerror(errno)));
}
