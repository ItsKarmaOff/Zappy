/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "quit" command for server clients
*/
/**
 * @file quit.c
 * @brief The file containing the handling of
 * the "quit" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_quit(
    server_t *server, client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Quit\" command");
    if (my_array_len((void **) args) != 1) {
        ERROR("Invalid number of arguments for \"Quit\" command");
        return;
    }
    my_exit(SUCCESS, GREEN "Server shutdown successfully." ENDL);
}
