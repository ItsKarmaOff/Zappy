/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The all.c
*/
/**
 * @file all.c
 * @brief The all.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_all(
    server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"All\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"All\" command");
        return;
    }
    display_server(server, true);
}
