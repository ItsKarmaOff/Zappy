/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "status" command for server clients
*/
/**
 * @file status.c
 * @brief The file containing the handling of
 * the "status" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_status(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Status\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Status\" command");
        return;
    }
    display_server(server, false);
}
