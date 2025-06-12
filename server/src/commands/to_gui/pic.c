/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The pic.c
*/
/**
 * @file pic.c
 * @brief The pic.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

static void send_pic(client_t *client,
    node_t *player_list, size_t level)
{
    dprintf(client->socket_fd, "pic %zu %zu %zu",
        ((player_t *)player_list->data)->position.x,
        ((player_t *)player_list->data)->position.y, level);
    for (node_t *node = player_list; node != NULL; node = node->next) {
        if (node->data != NULL)
            dprintf(client->socket_fd, " #%zu", ((player_t *)node->data)->id);
    }
    dprintf(client->socket_fd, "\n");
}

void send_pic_to_gui(server_t *server, client_t *client,
    node_t *player_list, size_t level)
{
    if (server == NULL || player_list == NULL || player_list->data == NULL)
        return;
    if (client != NULL) {
        send_pic(client, player_list, level);
        return;
    }
    for (size_t index = 0; index < server->current_clients_number; index++) {
        if (server->client_list[index]->client_type == CLIENT_GUI)
            send_pic(server->client_list[index],
                player_list, level);
    }
}
