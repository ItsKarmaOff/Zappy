/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The mct.c
*/
/**
 * @file mct.c
 * @brief The mct.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void handle_command_mct(server_t *server, client_t *client,
    char **args)
{
    DEBUG("Executing \"mct\" command\n");
    if (my_array_len((void **)args) != 1) {
        DEBUG("Invalid number of arguments for \"mct\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    send_mct_to_gui(server, client);
}
