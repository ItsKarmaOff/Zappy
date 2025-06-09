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

void send_bct_to_gui(server_t *server, vector2u_t position)
{
    tile_t *tile = NULL;

    if (server == NULL || position.x >= server->game.game_settings.width ||
    position.y >= server->game.game_settings.height)
        return;
    tile = &server->game.map[position.y][position.x];
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui) {
            dprintf(server->client_list[index]->socket_fd,
                "bct %zu %zu %d %d %d %d %d %d %d\n",
                position.x, position.y,
                (tile->resources & (1 << FOOD)) != 0,
                (tile->resources & (1 << LINEMATE)) != 0,
                (tile->resources & (1 << DERAUMERE)) != 0,
                (tile->resources & (1 << SIBUR)) != 0,
                (tile->resources & (1 << MENDIANE)) != 0,
                (tile->resources & (1 << PHIRAS)) != 0,
                (tile->resources & (1 << THYSTAME)) != 0);
        }
    }
}
