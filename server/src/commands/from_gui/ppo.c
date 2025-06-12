/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The ppo.c
*/
/**
 * @file ppo.c
 * @brief The ppo.c
 * @author Nicolas TORO
 */

#include "commands/commands_gui.h"

void handle_command_ppo_player(server_t *server, client_t *client,
    char **args)
{
    player_t *player = NULL;
    size_t player_id = my_get_number(args[1] + 1, DEFAULT_NB);

    if (my_errno != 0 ||
    player_id > server->game.game_settings.next_player_id) {
        DEBUG("Invalid player ID for \"ppo\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    player = get_player_by_id(&server->game, player_id);
    if (player == NULL) {
        DEBUG("Player not found for \"ppo\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    send_ppo_to_gui(server, client, player);
}

void handle_command_ppo(server_t *server, client_t *client,
    char **args)
{
    DEBUG("Executing \"ppo\" command\n");
    if (my_array_len((void **)args) != 2) {
        DEBUG("Invalid number of arguments for \"ppo\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    if (args[1][0] != '#') {
        DEBUG("Invalid player ID format for \"ppo\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    handle_command_ppo_player(server, client, args);
}
