/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The fork.c
*/
/**
 * @file fork.c
 * @brief The fork.c
 * @author Nicolas TORO
 */

#include "commands/commands_ai.h"

void handle_command_fork(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED char **args)
{
    player_t *new_player = NULL;

    DEBUG("Executing \"Fork\" command\n");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    resize_client_list(server, server->current_clients_number + 1);
    new_player = create_player_from_player(&server->game, client->player);
    AL(FALSE, my_push_front, &client->player->team->player_list,
        new_player, VOID);
    dprintf(client->socket_fd, VALID_AI);
    send_enw_to_gui(server, NULL, new_player);
}
