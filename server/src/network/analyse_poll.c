/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The analyse_poll.c
*/
/**
 * @file analyse_poll.c
 * @brief The analyse_poll.c
 * @author Nicolas TORO
 */

#include "network.h"

void analyse_poll(server_t *server, size_t index)
{
    if (server->poll_fds[index].revents & (POLLERR | POLLHUP | POLLNVAL)) {
        ERROR(my_create_str("Error on client %zu", index));
        return remove_client(server, index);
    }
    if (server->poll_fds[index].revents & POLLOUT)
        return write_client_action(server, index);
    if (server->poll_fds[index].revents & POLLIN) {
        if (server->poll_fds[index].fd == server->socket_fd)
            return add_new_client(server);
        return read_client_action(server, index);
    }
}
