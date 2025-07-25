/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "inventory" command for AI clients
*/
/**
 * @file inventory.c
 * @brief The file containing the handling of
 * the "inventory" command for AI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_ai.h"

void handle_ai_command_inventory(
    UNUSED server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"Inventory\" command");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    dprintf(client->socket_fd, "[ ");
    for (size_t i = 0; i < RESOURCES_SIZE; i++) {
        dprintf(client->socket_fd, "%s%s %zu", (i != 0) ? ", " : "",
            resources_names[i], client->player->inventory[i]);
    }
    dprintf(client->socket_fd, " ]\n");
}
