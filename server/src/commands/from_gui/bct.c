/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "bct" command for GUI clients
*/
/**
 * @file bct.c
 * @brief The file containing the handling of
 * the "bct" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

static bool check_args(server_t *server, client_t *client,
    char **args, vector2u_t *position)
{
    position->x = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != 0 || position->x >= server->game.game_settings.width) {
        DEBUG("Invalid x coordinate for \"bct\" command");
        send_sbp_to_gui(server, client);
        return false;
    }
    position->y = my_get_number(args[2], DEFAULT_NB);
    if (my_errno != 0 || position->y >= server->game.game_settings.height) {
        DEBUG("Invalid y coordinate for \"bct\" command");
        send_sbp_to_gui(server, client);
        return false;
    }
    return true;
}

void handle_gui_command_bct(
    server_t *server, client_t *client, char **args)
{
    vector2u_t position = {0};

    DEBUG("Executing \"bct\" command");
    if (my_array_len((void **)args) != 3) {
        DEBUG("Invalid number of arguments for \"bct\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    if (!check_args(server, client, args, &position))
        return;
    send_bct_to_gui(server, client, position);
}
