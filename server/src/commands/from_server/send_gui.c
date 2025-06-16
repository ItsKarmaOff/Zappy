/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The send_gui.c
*/
/**
 * @file send_gui.c
 * @brief The send_gui.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_send_gui(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Send GUI\" command");
    if (my_array_len((void **)args) != 2) {
        ERROR("Invalid number of arguments for \"Send GUI\" command");
        return;
    }
    for (size_t index = 1; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd, "%s\n", args[1]);
    }
}
