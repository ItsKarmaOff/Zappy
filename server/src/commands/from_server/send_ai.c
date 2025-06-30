/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "send_ai" command for server clients
*/
/**
 * @file send_ai.c
 * @brief The file containing the handling of
 * the "send_ai" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_send_ai(
    server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"Send AI\" command");
    if (my_array_len((void **)args) != 2) {
        ERROR("Invalid number of arguments for \"Send AI\" command");
        return;
    }
    for (size_t index = 1; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_AI)
            dprintf(server->client_list[index]->socket_fd, "%s\n", args[1]);
    }
}
