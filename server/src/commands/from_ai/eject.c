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

#include "commands/commands_ai.h"

static void destroy_egg(server_t *server, player_t *egg, node_t **to_delete)
{
    egg->team->eggs_number--;
    AL(FALSE, my_push_front, to_delete, egg, UNKNOWN);
    my_delete_nodes(&egg->team->player_list, egg, NULL);
    send_edi_to_gui(server, NULL, egg);
}

/** backup:
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
 */
static void move_player(server_t *server, player_t *player,
    orientation_t orientation, node_t **to_delete)
{
    AL(FALSE, my_push_front, to_delete, player, UNKNOWN);
    moves[orientation - 1].move_func(&server->game, player);
    AL(FALSE, my_push_back, &ACCESS_MAP(server->game.map, player).player_list,
        player, UNKNOWN);
    dprintf(player->client->socket_fd, "eject: %i\n", orientation);
    send_pex_to_gui(server, NULL, player);
    send_ppo_to_gui(server, NULL, player);
}

static void eject_players(server_t *server, client_t *client)
{
    bool fail = true;
    node_t *to_delete = NULL;

    for (node_t *tmp = ACCESS_MAP(server->game.map, client->player)
        .player_list; tmp != NULL; tmp = tmp->next) {
        if (((player_t *)tmp->data)->is_egg) {
            destroy_egg(server, tmp->data, &to_delete);
            fail = false;
        }
        if (!((player_t *)tmp->data)->is_egg && tmp->data != client->player) {
            move_player(server, tmp->data,
                client->player->orientation, &to_delete);
            fail = false;
        }
    }
    dprintf(client->socket_fd, (fail) ? WRONG_AI : VALID_AI);
    for (node_t *tmp = to_delete; tmp != NULL; tmp = tmp->next)
        my_delete_nodes(&ACCESS_MAP(server->game.map, client->player)
            .player_list, tmp->data, NULL);
    my_delete_list(&to_delete);
}

void handle_ai_command_eject(
    server_t *server, client_t *client, char **args)
{
    DEBUG("Executing \"Eject\" command");
    if (my_array_len((void **) args) != 1) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    eject_players(server, client);
}
