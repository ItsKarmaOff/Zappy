/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "pgt" command for GUI clients
*/
/**
 * @file pgt.c
 * @brief The file containing the sending of
 * the "pgt" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

void send_pgt_to_gui(server_t *server, client_t *client,
    player_t *player, resources_t resource_id)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        dprintf(client->socket_fd, "pgt #%zu %i\n",
            player->id, resource_id);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            dprintf(server->client_list[index]->socket_fd,
                "pgt #%zu %i\n", player->id, resource_id);
    }
}
