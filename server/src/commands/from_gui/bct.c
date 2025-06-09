/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The bct.c
*/
/**
 * @file bct.c
 * @brief The bct.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

static bool check_args(server_t *server, char **args, vector2u_t *position)
{
    position->x = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != 0 || position->x >= server->game.game_settings.width) {
        DEBUG("Invalid x coordinate for \"bct\" command\n");
        send_sbp_to_gui(server);
        return false;
    }
    position->y = my_get_number(args[2], DEFAULT_NB);
    if (my_errno != 0 || position->y >= server->game.game_settings.height) {
        DEBUG("Invalid y coordinate for \"bct\" command\n");
        send_sbp_to_gui(server);
        return false;
    }
    return true;
}

void handle_command_bct(server_t *server, UNUSED client_t *client,
    char **args)
{
    vector2u_t position = {0};

    DEBUG("Executing \"bct\" command\n");
    if (my_array_len((void **)args) != 3) {
        DEBUG("Invalid number of arguments for \"bct\" command\n");
        send_sbp_to_gui(server);
        return;
    }
    if (!check_args(server, args, &position))
        return;
    send_bct_to_gui(server, position);
}
