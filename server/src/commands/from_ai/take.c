/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The take.c
*/
/**
 * @file take.c
 * @brief The take.c
 * @author Nicolas TORO
 */

#include "commands/ai.h"

void handle_command_take(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED char **args)
{
    uint8_t i = 0;

    DEBUG("Executing \"Take\" command\n");
    if (my_array_len((void **) args) != 2) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    while (i < RESOURCES_SIZE) {
        if (strcmp(args[1], resources_names[i]))
            break;
        i++;
    }
    if (i == RESOURCES_SIZE
    || ACCESS_MAP(server->game.map, client->player).resources[i] == 0) {
        dprintf(client->socket_fd, WRONG_AI);
    } else {
        dprintf(client->socket_fd, VALID_AI);
        ACCESS_MAP(server->game.map, client->player).resources[i]--;
        client->player->inventory[i]++;
        server->game.resources[i].current_quantity--;
    }
}
