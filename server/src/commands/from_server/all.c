/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "all" internal server command
*/
/**
 * @file all.c
 * @brief The file containing the handling of
 * the "all" internal server command
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_all(
    server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"All\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"All\" command");
        return;
    }
    display_server(server, true);
}
