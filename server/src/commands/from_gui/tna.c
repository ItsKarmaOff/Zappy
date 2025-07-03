/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "tna" command for GUI clients
*/
/**
 * @file tna.c
 * @brief The file containing the handling of
 * the "tna" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void handle_gui_command_tna(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"tna\" command");
    if (my_array_len((void **)args) != 1) {
        DEBUG("Invalid number of arguments for \"tna\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    for (size_t index = 1; index < server->game.game_settings.teams_number;
    index++)
        send_tna_to_gui(server, client, server->game.team_list[index]);
}
