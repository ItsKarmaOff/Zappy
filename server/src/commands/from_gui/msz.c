/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "msz" command for GUI clients
*/
/**
 * @file msz.c
 * @brief The file containing the handling of
 * the "msz" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void handle_gui_command_msz(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"msz\" command");
    if (my_array_len((void **)args) != 1) {
        DEBUG("Invalid number of arguments for \"msz\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    send_msz_to_gui(server, client);
}
