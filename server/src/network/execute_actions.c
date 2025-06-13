/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The execute_actions.c
*/
/**
 * @file execute_actions.c
 * @brief The execute_actions.c
 * @author Nicolas TORO
 */

#include "network.h"

void execute_actions(server_t *server)
{
    client_t *client = NULL;

    for (size_t index = 0; index < server->current_clients_number; index++) {
        client = server->client_list[index];
        if (client->next_action.cmd_function != NULL &&
        difftime(time(NULL), client->last_action_time) >=
        client->next_action.time_to_wait /
        (double)server->game.game_settings.frequency) {
            DEBUG(my_create_str("Executing action for client %zu\n", index));
            client->next_action.cmd_function(server, client,
                client->next_action.action_args);
            FREE_WORD_ARRAY(client->next_action.action_args);
            client->next_action.cmd_function = NULL;
            client->next_action.action_args = NULL;
        }
    }
}
