/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "incantation" command for AI clients
*/
/**
 * @file incantation.c
 * @brief The file containing the handling of
 * the "incantation" command for AI clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_ai.h"

const incantation_t incantations[MAX_PLAYER_LEVEL - 1] = {
    {2, {0, 1, 0, 0, 0, 0, 0}},
    {2, {0, 1, 1, 1, 0, 0, 0}},
    {2, {0, 2, 0, 1, 0, 2, 0}},
    {4, {0, 1, 1, 2, 0, 1, 0}},
    {4, {0, 1, 2, 1, 3, 0, 0}},
    {6, {0, 1, 2, 3, 0, 1, 0}},
    {6, {0, 2, 2, 2, 2, 2, 1}}
};

static bool check_valid_resources(
    const game_t *game, const player_t *player)
{
    for (size_t i = 0; i < RESOURCES_SIZE; i++) {
        if (game->map[player->position.y][player->position.x].resources[i]
        < incantations[player->level - 1].required_resources[i])
            return false;
    }
    return true;
}

static bool check_valid_incantation(const game_t *game, const player_t *player)
{
    size_t player_count = 0;

    for (node_t *tmp = game->map[player->position.y][player->position.x]
    .player_list; tmp != NULL; tmp = tmp->next) {
        if (tmp->data != NULL && !((player_t *)tmp->data)->is_egg &&
        ((player_t *)tmp->data)->level == player->level &&
        ((player_t *)tmp->data)->is_incanting == false)
            player_count++;
    }
    if (player_count < incantations[player->level - 1].required_players)
        return false;
    return check_valid_resources(game, player);
}

static node_t *create_incantation(
    const game_t *game, const player_t *player)
{
    node_t *player_list = NULL;

    AL(FALSE, my_push_front, &player_list, (void *)player, UNKNOWN);
    for (node_t *tmp = game->map[player->position.y][player->position.x]
    .player_list; tmp != NULL; tmp = tmp->next) {
        if (tmp->data != NULL && !((player_t *)tmp->data)->is_egg
        && ((player_t *)tmp->data)->level == player->level
        && ((player_t *)tmp->data)->is_incanting == false
        && tmp->data != player)
            AL(FALSE,
                my_push_back, &player_list, (player_t *)tmp->data, UNKNOWN);
    }
    return player_list;
}

static node_t **get_incantation(const game_t *game, const player_t *player)
{
    for (node_t *tmp = ACCESS_MAP(game->map, player).incantation_list;
    tmp != NULL; tmp = tmp->next) {
        if (my_find_node(tmp->data, player, NULL))
            return (node_t **)&tmp->data;
    }
    return NULL;
}

static bool check_all_players_on_tile(
    const game_t *game, node_t *player_list)
{
    for (node_t *tmp = player_list; tmp != NULL; tmp = tmp->next) {
        if (my_find_node(ACCESS_MAP(game->map, ((player_t *)tmp->data))
        .player_list, tmp->data, NULL) == NULL)
            return false;
    }
    return true;
}

static void update_player_level(
    server_t *server, client_t *client, node_t **player_list)
{
    client->player->level++;
    client->player->is_incanting = false;
    dprintf(client->socket_fd, "Current level: %zu\n", client->player->level);
    send_plv_to_gui(server, NULL, client->player);
    if (my_list_size(*player_list) == 1) {
        send_pie_to_gui(server, NULL, client->player->position, true);
        for (size_t i = 0; i < RESOURCES_SIZE; i++)
            server->game.map[client->player->position.y]
            [client->player->position.x].resources[i] -=
                incantations[client->player->level - 2].required_resources[i];
        send_bct_to_gui(server, NULL, client->player->position);
        my_delete_nodes(&ACCESS_MAP(server->game.map, client->player)
            .incantation_list, *player_list, NULL);
    } else
        my_delete_nodes(player_list, client->player, NULL);
}

static void handle_ai_command_finish_incantation(
    server_t *server, client_t *client, UNUSED char **args)
{
    node_t **player_list = get_incantation(&server->game, client->player);

    DEBUG("Finish \"Incantation\" command");
    if (player_list == NULL || check_valid_resources(&server->game,
    client->player) == false ||
    check_all_players_on_tile(&server->game, *player_list) == false) {
        if (player_list == NULL || client->player == (*player_list)->data)
            send_pie_to_gui(server, NULL, client->player->position, false);
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    update_player_level(server, client, player_list);
}

static void update_players_in_incantation(
    server_t *server, node_t *player_list)
{
    for (node_t *tmp = player_list; tmp != NULL; tmp = tmp->next) {
        dprintf(((player_t *) tmp->data)->client->socket_fd, ELEVATION_OK);
        ((player_t *)tmp->data)->is_incanting = true;
        if (((player_t *)tmp->data)->client->next_action.cmd_function) {
            my_push_front(&((player_t *)tmp->data)->client->command_queue,
                my_strdup("\n"), STRING);
            my_push_front(&((player_t *)tmp->data)->client->command_queue,
                my_word_array_to_str(((player_t *)tmp->data)->client
                ->next_action.action_args, " "), STRING);
            server->poll_fds[get_client_index(server,
                ((player_t *)tmp->data)->client)].events |= POLLOUT;
        }
        FREE_WORD_ARRAY(((player_t *)tmp->data)->client
            ->next_action.action_args);
        ((player_t *)tmp->data)->client->next_action.action_args = NULL;
        ((player_t *)tmp->data)->client->next_action.time_to_wait = 300;
        ((player_t *)tmp->data)->client->next_action.cmd_function =
            &handle_ai_command_finish_incantation;
        ((player_t *)tmp->data)->client->last_action_time = my_get_time();
    }
}

void handle_ai_command_incantation(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    node_t *player_list = NULL;

    DEBUG("Executing \"Incantation\" command");
    if (my_array_len((void **) args) != 1 || check_valid_incantation(
    &server->game, client->player) == false) {
        dprintf(client->socket_fd, WRONG_AI);
        return;
    }
    player_list = create_incantation(&server->game, client->player);
    AL(FALSE, my_push_front, &ACCESS_MAP(server->game.map, client->player)
        .incantation_list, player_list, VOID);
    my_update_malloc(FALSE);
    update_players_in_incantation(server, player_list);
    my_update_malloc(TRUE);
    send_pic_to_gui(server, NULL, player_list, client->player->level);
}
