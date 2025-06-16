/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The status.c
*/
/**
 * @file status.c
 * @brief The status.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_status(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Status\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Status\" command");
        return;
    }
    display_server(server, false);
}
