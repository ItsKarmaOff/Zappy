/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The write_client_action.c
*/
/**
 * @file write_client_action.c
 * @brief The write_client_action.c
 * @author Nicolas TORO
 */

#include "network.h"

void write_client_action(server_t *server, size_t index)
{
    server->poll_fds[index].events &= ~POLLOUT;
}
