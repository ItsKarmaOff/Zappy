/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The pin.c
*/
/**
 * @file pin.c
 * @brief The pin.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void send_pin(client_t *client, player_t *player)
{
    if (client == NULL || player == NULL)
        return;
    dprintf(client->socket_fd,
        "pin #%zu %zu %zu %zu %zu %zu %zu %zu %zu %zu\n",
        player->id, player->position.x, player->position.y,
        player->inventory[FOOD], player->inventory[LINEMATE],
        player->inventory[DERAUMERE], player->inventory[SIBUR],
        player->inventory[MENDIANE], player->inventory[PHIRAS],
        player->inventory[THYSTAME]);
}

void send_pin_to_gui(server_t *server, client_t *client,
    player_t *player)
{
    if (server == NULL || player == NULL)
        return;
    if (client != NULL) {
        send_pin(client, player);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->is_gui)
            send_pin(server->client_list[index], player);
    }
}
