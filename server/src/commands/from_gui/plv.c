/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The plv.c
*/
/**
 * @file plv.c
 * @brief The plv.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void handle_command_plv_player(server_t *server, client_t *client,
    char **args)
{
    player_t *player = NULL;
    size_t player_id = my_get_number(args[1] + 1, DEFAULT_NB);

    if (my_errno != 0 ||
    player_id > server->game.game_settings.next_player_id) {
        DEBUG("Invalid player ID for \"plv\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    player = get_player_by_id(&server->game, player_id);
    if (player == NULL) {
        DEBUG("Player not found for \"plv\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    send_plv_to_gui(server, client, player);
}

void handle_command_plv(server_t *server, client_t *client,
    char **args)
{
    DEBUG("Executing \"plv\" command\n");
    if (my_array_len((void **)args) != 2) {
        DEBUG("Invalid number of arguments for \"plv\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    if (args[1][0] != '#') {
        DEBUG("Invalid player ID format for \"plv\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    handle_command_plv_player(server, client, args);
}
