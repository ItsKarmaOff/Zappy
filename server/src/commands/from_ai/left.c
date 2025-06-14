/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The left.c
*/
/**
 * @file left.c
 * @brief The left.c
 * @author Nicolas TORO
 */

#include "commands/commands_ai.h"

void handle_ai_command_left(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"Left\" command\n");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    client->player->orientation = (client->player->orientation + 2) % 4 + 1;
    dprintf(client->socket_fd, VALID_AI);
    send_ppo_to_gui(server, NULL, client->player);
}
