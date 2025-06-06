/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The add_new_client.c
*/
/**
 * @file add_new_client.c
 * @brief The add_new_client.c
 * @author Nicolas TORO
 */

#include "network.h"

static bool is_valid_team(server_t *server, char *team_name)
{
    for (size_t index = 0; index < server->game.game_settings.teams_number;
    index++) {
        if (my_strcmp(team_name, server->game.team_list[index]->name) == 0)
            return true;
    }
    return false;
}

static void add_player_to_graphic(server_t *server, client_t *new_client,
    size_t team_index)
{
    player_t *new_player = create_player(&server->game,
        server->game.team_list[team_index]);

    resize_client_list(server, server->max_clients_number + 1);
    AL(FALSE, my_push_front, &server->game.team_list[team_index]
        ->player_list, new_player, VOID);
}

static bool check_team_size(server_t *server, client_t *new_client,
    char *team_name)
{
    size_t team_index = get_team_index(&server->game, team_name);

    if (get_nb_empty_slots(server->game.team_list[team_index]) == 0) {
        if (team_index == GRAPHIC_TEAM_INDEX) {
            add_player_to_graphic(server, new_client, team_index);
            return true;
        }
        dprintf(new_client->socket_fd, "0\n");
        close(new_client->socket_fd);
        FREE(new_client);
        ERROR(my_create_str("Client tried to join a full team: %s\n",
            team_name));
        FREE(team_name);
        return false;
    }
    return true;
}

static bool check_team(server_t *server, client_t *new_client, char *team_name)
{
    if (!is_valid_team(server, team_name)) {
        dprintf(new_client->socket_fd, WRONG_AI);
        close(new_client->socket_fd);
        FREE(new_client);
        ERROR(my_create_str("Client tried to join an invalid team: %s\n",
            team_name));
        FREE(team_name);
        return false;
    }
    return check_team_size(server, new_client, team_name);
}

static void init_gui(server_t *server, int socket_fd)
{
    dprintf(socket_fd, "sza %zu %zu\n",
        server->game.game_settings.width,
        server->game.game_settings.height);
}

static void respond_to_client(server_t *server, client_t *new_client,
    size_t team_index)
{
    if (team_index != GRAPHIC_TEAM_INDEX) {
        dprintf(new_client->socket_fd, "%zu\n",
            get_nb_empty_slots(server->game.team_list[team_index]));
        dprintf(new_client->socket_fd, "%zu %zu\n",
            server->game.game_settings.width,
            server->game.game_settings.height);
    } else {
        new_client->is_gui = true;
        init_gui(server, new_client->socket_fd);
    }
}

static void add_client_to_server(server_t *server, client_t *new_client,
    char *team_name)
{
    size_t team_index = get_team_index(&server->game, team_name);

    respond_to_client(server, new_client, team_index);
    new_client->player = get_next_egg(server->game.team_list[team_index]);
    server->poll_fds[server->current_clients_number + 1].fd =
        new_client->socket_fd;
    server->poll_fds[server->current_clients_number + 1].events = POLLIN;
    server->client_list[server->current_clients_number] = new_client;
    server->current_clients_number += 1;
    DEBUG(my_create_str("New client added in %s\n", team_name));
    FREE(team_name);
}

void add_new_client(server_t *server)
{
    client_t *new_client = AL(FALSE, my_calloc, 1, sizeof(client_t));
    socklen_t client_size = sizeof(new_client->address);
    char *team_name = NULL;

    new_client->socket_fd = accept(server->socket_fd,
        (struct sockaddr *)&new_client->address, &client_size);
    if (new_client->socket_fd == -1) {
        FREE(new_client);
        THROW(my_create_str("EXCEPTION: accept client: %s\n", STRERR));
    }
    dprintf(new_client->socket_fd, WELCOME_MESSAGE);
    team_name = get_response(new_client->socket_fd);
    if (check_team(server, new_client, team_name) == false)
        return;
    add_client_to_server(server, new_client, team_name);
}
