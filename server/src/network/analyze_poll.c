/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function to analyze poll events
*/
/**
 * @file analyze_poll.c
 * @brief The file containing the function to analyze poll events
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "network.h"

void analyze_poll(server_t *server, size_t index)
{
    if (server->poll_fds[index].fd != STDIN &&
    server->poll_fds[index].revents & (POLLERR | POLLHUP | POLLNVAL)) {
        ERROR(my_create_str("Error on client %zu "
            "(the client stop the connection)", index - 1));
        return remove_client(server, index);
    }
    if (server->poll_fds[index].revents & POLLOUT)
        write_client_action(server, index);
    if (server->poll_fds[index].revents & POLLIN) {
        if (server->poll_fds[index].fd == server->socket_fd)
            return add_new_client(server);
        return read_client_action(server, index);
    }
}
