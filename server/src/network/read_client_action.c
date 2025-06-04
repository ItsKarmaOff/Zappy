/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The read_client_action.c
*/
/**
 * @file read_client_action.c
 * @brief The read_client_action.c
 * @author Nicolas TORO
 */

#include "network.h"

static void disconnect_client(server_t *server, size_t index)
{
    DEBUG(my_create_str("Client %zu disconnected\n", index));
    remove_client(server, index);
}

void read_client_action(server_t *server, size_t index)
{
    size_t read_size = 0;
    char *command = NULL;

    if (ioctl(server->poll_fds[index].fd, FIONREAD, &read_size) < 0)
        THROW(my_create_str("EXCEPTION: ioctl failed: %s\n", STRERR));
    if (read_size == 0)
        return disconnect_client(server, index);
    command = AL(FALSE, my_calloc, read_size + 1, sizeof(char));
    if (read(server->poll_fds[index].fd, command, read_size) < 0) {
        FREE(command);
        disconnect_client(server, index);
    }
    AL(FALSE, my_push_back, &server->client_list[index -1]->command_queue,
        command, STRING);
    if (my_str_contains(command, "\n"))
        server->poll_fds[index].events |= POLLOUT;
}
