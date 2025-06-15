/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The clients.c
*/
/**
 * @file clients.c
 * @brief The clients.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

static void display_clients(server_t *server)
{
    for (size_t index = 1; index < server->current_clients_number; index++) {
        printf("- %zu: %s", index, server->client_list[index]->client_type
            == CLIENT_AI ? "AI" : "GUI");
        if (server->client_list[index]->player != NULL)
            printf(" -> Player #%zu (team: %s)\n",
                server->client_list[index]->player->id,
                server->client_list[index]->player->team->name);
        else
            printf("\n");
    }
}

void handle_server_command_clients(
    server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"Clients\" command");
    if (my_array_len((void **) args) != 1) {
        ERROR("Invalid number of arguments for \"Clients\" command");
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Current clients:" ENDL);
    if (server->current_clients_number <= 1)
        printf("No clients connected.\n");
    else
        display_clients(server);
    my_putstr("========================================"
        "========================================\n");
}
