/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The authenticate_client.c
*/
/**
 * @file authenticate_client.c
 * @brief The authenticate_client.c
 * @author Nicolas TORO
 */

#include "network.h"

static bool check_team_size(server_t *server, size_t index,
    char *team_name, char *next_team_name)
{
    size_t team_index = get_team_index(&server->game, team_name);

    if (team_index != GRAPHIC_TEAM_INDEX &&
    server->game.team_list[team_index]->eggs_number == 0) {
        dprintf(CLIENT(server, index)->socket_fd, WRONG_AI);
        ERROR(my_create_str("Client %zu tried to join a full team: %s",
            index, team_name));
        FREE(CLIENT(server, index)->team_name);
        FREE(team_name);
        CLIENT(server, index)->team_name = next_team_name;
        if (!my_str_contains(CLIENT(server, index)->team_name, "\n"))
            server->poll_fds[index].events &= ~POLLOUT;
        return false;
    }
    return true;
}

static bool check_team(server_t *server, size_t index,
    char *team_name, char *next_team_name)
{
    if (!is_valid_team(server, team_name)) {
        dprintf(CLIENT(server, index)->socket_fd, WRONG_AI);
        ERROR(my_create_str("Client %zu tried to join an invalid team: %s",
            index, team_name));
        FREE(CLIENT(server, index)->team_name);
        FREE(team_name);
        CLIENT(server, index)->team_name = next_team_name;
        if (!my_str_contains(CLIENT(server, index)->team_name, "\n"))
            server->poll_fds[index].events &= ~POLLOUT;
        return false;
    }
    return check_team_size(server, index, team_name, next_team_name);
}

static void send_team_to_gui(server_t *server, client_t *client,
    team_t *team)
{
    send_tna_to_gui(server, client, team);
    for (node_t *player = team->player_list; player != NULL;
    player = player->next) {
        if (player->data == NULL)
            continue;
        if (((player_t *)player->data)->is_egg) {
            send_enw_to_gui(server, client, (player_t *)player->data);
            continue;
        }
        send_pnw_to_gui(server, client, (player_t *)player->data);
        send_pin_to_gui(server, client, (player_t *)player->data);
    }
}

static void init_gui(server_t *server, client_t *client)
{
    send_msz_to_gui(server, client);
    send_sgt_to_gui(server, client);
    send_mct_to_gui(server, client);
    for (size_t index = 1; index < server->game.game_settings.teams_number;
    index++)
        send_team_to_gui(server, client, server->game.team_list[index]);
    if (server->game.winner_team_name != NULL)
        send_seg_to_gui(server, client);
}

static void respond_to_client(server_t *server, client_t *client,
    size_t team_index)
{
    if (team_index != GRAPHIC_TEAM_INDEX) {
        dprintf(client->socket_fd, "%zu\n",
            server->game.team_list[team_index]->eggs_number - 1);
        dprintf(client->socket_fd, "%zu %zu\n",
            server->game.game_settings.width,
            server->game.game_settings.height);
    } else {
        client->client_type = CLIENT_GUI;
        init_gui(server, client);
    }
}

void accept_client(server_t *server, size_t index,
    char *team_name, char *next_team_name)
{
    size_t team_index = get_team_index(&server->game, team_name);

    respond_to_client(server, CLIENT(server, index), team_index);
    CLIENT(server, index)->player =
        get_next_egg(server, server->game.team_list[team_index]);
    if (CLIENT(server, index)->player != NULL)
        CLIENT(server, index)->player->client = CLIENT(server, index);
    FREE(CLIENT(server, index)->team_name);
    CLIENT(server, index)->team_name = team_name;
    AL(FALSE, my_push_back, &CLIENT(server, index)->command_queue,
        next_team_name, STRING);
    CLIENT(server, index)->is_authenticated = true;
    if (!my_str_contains(next_team_name, "\n"))
        server->poll_fds[index].events &= ~POLLOUT;
    DEBUG(my_create_str("Client %zu authenticated with team: %s",
        index - 1, CLIENT(server, index)->team_name));
}

void authenticate_client(server_t *server, size_t index)
{
    char *team_name = AL(FALSE, my_strndup, CLIENT(server, index)->team_name,
        my_get_char_index(CLIENT(server, index)->team_name, '\n', 1));
    char *next_team_name = AL(FALSE, my_strdup, my_strstr(
        CLIENT(server, index)->team_name, "\n") + 1);

    if (!check_team(server, index, team_name, next_team_name))
        return;
    accept_client(server, index, team_name, next_team_name);
}
