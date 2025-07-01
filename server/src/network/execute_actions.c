/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function to execute actions for clients
*/
/**
 * @file execute_actions.c
 * @brief The file containing the function to execute actions for clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "network.h"

void execute_actions(server_t *server)
{
    client_t *client = NULL;
    action_t action = {NULL, 0, NULL};

    for (size_t index = 0; index < server->current_clients_number; index++) {
        client = server->client_list[index];
        if (server->game.game_settings.is_paused
        && client->client_type == CLIENT_AI)
            continue;
        if (client->next_action.cmd_function != NULL &&
        my_difftime(my_get_time(), client->last_action_time) >=
        client->next_action.time_to_wait /
        (double)server->game.game_settings.frequency) {
            action = client->next_action;
            client->next_action.cmd_function = NULL;
            client->next_action.action_args = NULL;
            action.cmd_function(server, client, action.action_args);
            client->last_action_time = my_get_time();
            FREE_WORD_ARRAY(action.action_args);
        }
    }
}
