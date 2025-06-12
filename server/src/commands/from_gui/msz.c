/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The msz.c
*/
/**
 * @file msz.c
 * @brief The msz.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void handle_command_msz(server_t *server, client_t *client,
    char **args)
{
    DEBUG("Executing \"msz\" command\n");
    if (my_array_len((void **)args) != 1) {
        DEBUG("Invalid number of arguments for \"msz\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    send_msz_to_gui(server, client);
}
