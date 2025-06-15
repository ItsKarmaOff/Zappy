/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The client.c
*/
/**
 * @file client.c
 * @brief The client.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

static void display_client(server_t *server, size_t client_id)
{
    my_putstr(BOLD UNDERLINE "Client Information:" ENDL);
    printf(BOLD "- Client ID:" RESET " %zu\n", client_id);
    printf(BOLD "- Client Type:" RESET " %s\n",
        server->client_list[client_id]->client_type == CLIENT_AI ?
            "AI" : "GUI");
    if (server->client_list[client_id]->player != NULL)
        display_player(server->client_list[client_id]->player, "");
}

void handle_server_command_client(
    server_t *server, UNUSED client_t *client, char **args)
{
    size_t client_id = 0;

    DEBUG("Executing \"Client\" command");
    if (my_array_len((void **) args) != 2) {
        ERROR("Invalid number of arguments for \"Client\" command");
        return;
    }
    client_id = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || client_id == 0
    || client_id >= server->current_clients_number) {
        ERROR(my_create_str("Invalid client ID: %s", args[1]));
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    display_client(server, client_id);
    my_putstr("========================================"
        "========================================\n");
}
