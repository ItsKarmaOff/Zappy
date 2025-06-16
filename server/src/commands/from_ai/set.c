/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The set.c
*/
/**
 * @file set.c
 * @brief The set.c
 * @author Nicolas TORO
 */

#include "commands/ai.h"

void handle_command_set(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED char **args)
{
    size_t i = 0;

    DEBUG("Executing \"Set\" command\n");
    if (my_array_len((void **) args) != 2) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    for (; i < RESOURCES_SIZE; i++) {
        if (strcmp(args[1], resources_names[i]) == 0)
            break;
    }
    if (i == RESOURCES_SIZE
    || client->player->inventory[i] == 0) {
        dprintf(client->socket_fd, WRONG_AI);
    } else {
        dprintf(client->socket_fd, VALID_AI);
        client->player->inventory[i]--;
        ACCESS_MAP(server->game.map, client->player).resources[i]++;
        server->game.resources[i].current_quantity++;
    }
}
