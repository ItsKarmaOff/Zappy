/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "sst" command for GUI clients
*/
/**
 * @file sst.c
 * @brief The file containing the handling of
 * the "sst" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void handle_gui_command_sst(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"sst\" command");
    if (my_array_len((void **)args) != 2) {
        DEBUG("Invalid number of arguments for \"sst\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    server->game.game_settings.frequency =
        my_get_number(args[1], DEFAULT_NB);
    if (my_errno != 0 || server->game.game_settings.frequency == 0) {
        DEBUG("Invalid frequency for \"sst\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    send_sst_to_gui(server, client);
}
