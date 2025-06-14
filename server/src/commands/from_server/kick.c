/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The kick.c
*/
/**
 * @file kick.c
 * @brief The kick.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_kick(
    server_t *server, UNUSED client_t *client, char **args)
{
    size_t client_id = 0;

    DEBUG("Executing \"Kick\" command\n");
    if (my_array_len((void **) args) != 2) {
        ERROR("Invalid number of arguments for \"Kick\" command\n");
        return;
    }
    client_id = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || client_id == 0
    || client_id > server->current_clients_number) {
        ERROR(my_create_str("Invalid client ID: %s\n", args[1]));
        return;
    }
    remove_client(server, client_id + 1);
    printf("Client %zu has been kicked from the server.\n", client_id);
}
