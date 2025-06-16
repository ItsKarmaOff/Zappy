/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The look.c
*/
/**
 * @file look.c
 * @brief The look.c
 * @author Nicolas TORO
 */

#include "commands/ai.h"

static void send_tiles(server_t *server, client_t *client, long x, long y)
{
    tile_t *tile = &(server->game.map
    [(client->player->position.y + y + server->game.game_settings.height)
    % server->game.game_settings.height]
    [(client->player->position.x + x + server->game.game_settings.width)
    % server->game.game_settings.width]);

    for (node_t *tmp = tile->clients; tmp != NULL; tmp = tmp->next) {
        dprintf(client->socket_fd, " %s", ((player_t *)tmp->data)->is_egg
        ? "egg" : "player");
    }
    for (size_t i = 0; i < RESOURCES_SIZE; i++) {
        for (size_t j = 0; j < tile->resources[i]; j++) {
            dprintf(client->socket_fd, " %s", resources_names[i]);
        }
    }
}

void handle_command_look(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED char **args)
{
    orientation_t orientation = client->player->orientation;

    DEBUG("Executing \"Look\" command\n");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    dprintf(client->socket_fd, "[");
    for (long i = 0; i < (long)client->player->level + 1; i++) {
        for (long j = 0 - i; j < i + 1; j++) {
            dprintf(client->socket_fd, (i != 0) ? "," : "");
            send_tiles(server, client,
            (orientation % 2) ? j * (2 - (long)orientation)
            : i * (3 - (long)orientation),
            (orientation % 2) ? i * ((long)orientation - 2)
            : j * ((long)orientation - 3));
        }
    }
    dprintf(client->socket_fd, " ]\n");
}
