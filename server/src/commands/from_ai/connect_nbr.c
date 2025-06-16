/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The connect_nbr.c
*/
/**
 * @file connect_nbr.c
 * @brief The connect_nbr.c
 * @author Nicolas TORO
 */

#include "commands/commands_ai.h"

void handle_ai_command_connect_nbr(
    UNUSED server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"Connect_nbr\" command");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    dprintf(client->socket_fd, "%zu\n", client->player->team->eggs_number);
}
