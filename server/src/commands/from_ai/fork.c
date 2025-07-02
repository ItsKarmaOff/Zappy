/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "fork" command for AI clients
*/
/**
 * @file fork.c
 * @brief The file containing the handling of
 * the "fork" command for AI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_ai.h"

void handle_ai_command_fork(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    player_t *new_player = NULL;

    DEBUG("Executing \"Fork\" command");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    new_player = create_player_from_player(&server->game, client->player);
    AL(FALSE, my_push_back, &client->player->team->player_list,
        new_player, VOID);
    dprintf(client->socket_fd, VALID_AI);
    send_enw_to_gui(server, NULL, new_player);
}
