/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The sgt.c
*/
/**
 * @file sgt.c
 * @brief The sgt.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void handle_gui_command_sgt(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"sgt\" command\n");
    if (my_array_len((void **)args) != 1) {
        DEBUG("Invalid number of arguments for \"sgt\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    send_sgt_to_gui(server, client);
}
