/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The clear.c
*/
/**
 * @file clear.c
 * @brief The clear.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_clear(
    UNUSED server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"Clear\" command\n");
    if (my_array_len((void **) args) != 1) {
        ERROR("Invalid number of arguments for \"Clear\" command\n");
        return;
    }
    system("clear");
}
//backup: my_putstr("\033[H\033[J");
