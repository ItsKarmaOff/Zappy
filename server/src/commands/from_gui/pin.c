/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "pin" command for GUI clients
*/
/**
 * @file pin.c
 * @brief The file containing the handling of
 * the "pin" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void handle_command_pin_player(server_t *server, client_t *client,
    char **args)
{
    player_t *player = NULL;
    size_t player_id = my_get_number(args[1] + 1, DEFAULT_NB);

    if (my_errno != 0 ||
    player_id > server->game.game_settings.next_player_id) {
        DEBUG("Invalid player ID for \"pin\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    player = get_player_by_id(&server->game, player_id);
    if (player == NULL) {
        DEBUG("Player not found for \"pin\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    send_pin_to_gui(server, client, player);
}

void handle_gui_command_pin(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"pin\" command");
    if (my_array_len((void **)args) != 2) {
        DEBUG("Invalid number of arguments for \"pin\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    if (args[1][0] != '#') {
        DEBUG("Invalid player ID format for \"pin\" command");
        send_sbp_to_gui(server, client);
        return;
    }
    handle_command_pin_player(server, client, args);
}
