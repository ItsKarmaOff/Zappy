/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The eject.c
*/
/**
 * @file eject.c
 * @brief The eject.c
 * @author Nicolas TORO
 */

#include "commands/ai.h"

static void destroy_egg(tile_t **map, player_t *egg)
{
    egg->team->eggs_number--;
    my_free_ptr(my_pop_node(&(ACCESS_MAP(map, egg).clients), egg, NULL));
    my_free_ptr(my_pop_node(&egg->team->player_list, egg, NULL));
    my_free_ptr(egg);
}

static void move_player(game_t *game, player_t *player,
    orientation_t orientation)
{
    my_free_ptr(my_pop_node(&(ACCESS_MAP(game->map, player).clients),
    player, NULL));
    player->position.x = ((long)player->position.x +
        game->game_settings.width + !((long)orientation % 2)
        * (3 - (long)orientation)) % game->game_settings.width;
    player->position.y = ((long)player->position.y +
        game->game_settings.height + ((long)orientation % 2)
        * ((long)orientation - 2)) % game->game_settings.height;
    my_push_back(&(ACCESS_MAP(game->map, player).clients), player, UNKNOWN);
    if ((long)orientation - (long)player->orientation == 0)
        dprintf(player->client->socket_fd, "eject: %d\n", 5);
    if ((long)orientation - (long)player->orientation == 2
    || (long)player->orientation - (long)orientation == 2)
        dprintf(player->client->socket_fd, "eject: %d\n", 1);
    if ((long)orientation - (long)player->orientation == 1
    || (long)player->orientation - (long)orientation == 1)
        dprintf(player->client->socket_fd, "eject: %d\n", 3);
    if ((long)orientation - (long)player->orientation == 3
    || (long)player->orientation - (long)orientation == 3)
        dprintf(player->client->socket_fd, "eject: %d\n", 7);
}

void handle_command_eject(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED char **args)
{
    bool fail = true;

    DEBUG("Executing \"Eject\" command\n");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    for (node_t *tmp = ACCESS_MAP(server->game.map, client->player).clients;
    tmp != NULL; tmp = tmp->next) {
        if (((player_t *)tmp->data)->is_egg) {
            destroy_egg(server->game.map, tmp->data);
            fail = false;
        }
        if (!((player_t *)tmp->data)->is_egg && tmp->data != client->player) {
            move_player(&server->game, tmp->data,
                client->player->orientation);
            fail = false;
        }
    }
    dprintf(client->socket_fd, (fail) ? WRONG_AI : VALID_AI);
}
