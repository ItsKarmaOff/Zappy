/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The quit.c
*/
/**
 * @file quit.c
 * @brief The quit.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_command_quit(server_t *server, client_t *client,
    UNUSED char **args)
{
    DEBUG("Executing \"Quit\" command\n");
    if (my_array_len((void **) args) != 1) {
        ERROR("Invalid number of arguments for \"Quit\" command\n");
        return;
    }
    my_exit(SUCCESS, GREEN "Server shutdown successfully.\n" RESET);
}
