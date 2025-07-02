/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "look" command for AI clients
*/
/**
 * @file look.c
 * @brief The file containing the handling of
 * the "look" command for AI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_ai.h"

static void send_tiles(server_t *server, client_t *client,
    ssize_t x, ssize_t y)
{
    tile_t *tile = &(server->game.map
        [(client->player->position.y + y + server->game.game_settings.height)
        % server->game.game_settings.height]
        [(client->player->position.x + x + server->game.game_settings.width)
        % server->game.game_settings.width]);

    for (node_t *tmp = tile->player_list; tmp != NULL; tmp = tmp->next) {
        if (((player_t *)tmp->data)->is_egg &&
        server->game.game_settings.show_eggs)
            dprintf(client->socket_fd, " egg");
        if (!((player_t *)tmp->data)->is_egg)
            dprintf(client->socket_fd, " player");
    }
    for (size_t i = 0; i < RESOURCES_SIZE; i++) {
        for (size_t j = 0; j < tile->resources[i]; j++)
            dprintf(client->socket_fd, " %s", resources_names[i]);
    }
}

void handle_ai_command_look(
    server_t *server, client_t *client, char **args)
{
    orientation_t orientation = client->player->orientation;

    DEBUG("Executing \"Look\" command");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    dprintf(client->socket_fd, "[");
    for (ssize_t i = 0; i < (ssize_t)client->player->level + 1; i++) {
        for (ssize_t j = 0 - i; j < i + 1; j++) {
            dprintf(client->socket_fd, (i != 0) ? "," : "");
            send_tiles(server, client,
                (orientation % 2) ? j * (2 - (ssize_t)orientation)
                : i * (3 - (ssize_t)orientation),
                (orientation % 2) ? i * ((ssize_t)orientation - 2)
                : j * ((ssize_t)orientation - 3));
        }
    }
    dprintf(client->socket_fd, " ]\n");
}
