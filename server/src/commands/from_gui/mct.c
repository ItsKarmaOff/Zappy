/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "mct" command for GUI clients
*/
/**
 * @file mct.c
 * @brief The file containing the handling of
 * the "mct" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void handle_gui_command_mct(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"mct\" command");
    if (my_array_len((void **)args) != 1) {
        DEBUG("Invalid number of arguments for \"mct\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    send_mct_to_gui(server, client);
}
