/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "connect_nbr" command for AI clients
*/
/**
 * @file connect_nbr.c
 * @brief The file containing the handling of
 * the "connect_nbr" command for AI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
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
