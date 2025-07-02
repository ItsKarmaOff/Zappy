/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the sending of the "bct" command for GUI clients
*/
/**
 * @file bct.c
 * @brief The file containing the sending of
 * the "bct" command for GUI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_gui.h"

static void send_bct(client_t *client, tile_t *tile)
{
    if (client == NULL || tile == NULL)
        return;
    dprintf(client->socket_fd, "bct %zu %zu %zu %zu %zu %zu %zu %zu %zu\n",
        tile->position.x, tile->position.y,
        tile->resources[FOOD],
        tile->resources[LINEMATE],
        tile->resources[DERAUMERE],
        tile->resources[SIBUR],
        tile->resources[MENDIANE],
        tile->resources[PHIRAS],
        tile->resources[THYSTAME]);
}

void send_bct_to_gui(server_t *server, client_t *client,
    vector2u_t position)
{
    tile_t *tile = NULL;

    if (server == NULL || position.x >= server->game.game_settings.width ||
    position.y >= server->game.game_settings.height)
        return;
    tile = &server->game.map[position.y][position.x];
    if (client != NULL) {
        send_bct(client, tile);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            send_bct(server->client_list[index], tile);
    }
}
