/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "clear" command for server clients
*/
/**
 * @file clear.c
 * @brief The file containing the handling of
 * the "clear" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_clear(
    UNUSED server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"Clear\" command");
    if (my_array_len((void **) args) != 1) {
        ERROR("Invalid number of arguments for \"Clear\" command");
        return;
    }
    system("clear");
}
//backup: my_putstr("\033[H\033[J");
