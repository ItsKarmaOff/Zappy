/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "right" command for AI clients
*/
/**
 * @file right.c
 * @brief The file containing the handling of
 * the "right" command for AI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_ai.h"

void handle_ai_command_right(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"Right\" command");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    client->player->orientation = (client->player->orientation % 4) + 1;
    dprintf(client->socket_fd, VALID_AI);
    send_ppo_to_gui(server, NULL, client->player);
}
