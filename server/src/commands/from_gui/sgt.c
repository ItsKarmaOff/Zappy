/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "sgt" command for GUI clients
*/
/**
 * @file sgt.c
 * @brief The file containing the handling of
 * the "sgt" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void handle_gui_command_sgt(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"sgt\" command");
    if (my_array_len((void **)args) != 1) {
        DEBUG("Invalid number of arguments for \"sgt\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    send_sgt_to_gui(server, client);
}
