/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function to read client actions
*/
/**
 * @file read_client_action.c
 * @brief The file containing the function to read client actions
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "network.h"

static void disconnect_client(server_t *server, size_t index,
    char *read_buffer)
{
    DEBUG(my_create_str("Client %zu disconnected", index - 1));
    FREE(read_buffer);
    remove_client(server, index);
}

static bool is_queue_full(client_t *client, size_t index, char *command)
{
    size_t nb_command = 0;

    if (client->client_type != CLIENT_AI)
        return false;
    for (node_t *tmp = client->command_queue; tmp != NULL; tmp = tmp->next) {
        nb_command += my_count_letter(tmp->data, '\n');
        if (nb_command >= CLIENT_MAX_COMMANDS)
            return true;
    }
    if (nb_command >= CLIENT_MAX_COMMANDS - 1
    && client->next_action.cmd_function != NULL)
        return true;
    if (my_count_letter(command, '\n') + nb_command >= CLIENT_MAX_COMMANDS) {
        my_replace_char_at(command, '\n', '\0',
            CLIENT_MAX_COMMANDS - nb_command + 1);
        WARNING(my_create_str("Too many commands read from client %zu, "
            "skipping some commands", index));
    }
    return false;
}

static void read_authenticated_client_action(server_t *server, size_t index)
{
    size_t read_size = 0;
    char *command = NULL;

    if (ioctl(server->poll_fds[index].fd, FIONREAD, &read_size) < 0)
        THROW(my_create_str("EXCEPTION: ioctl failed: %s", STRERR));
    if (read_size == 0)
        return disconnect_client(server, index, command);
    command = AL(FALSE, my_calloc, read_size + 1, sizeof(char));
    if (read(server->poll_fds[index].fd, command, read_size) < 0)
        return disconnect_client(server, index, command);
    if (is_queue_full(server->client_list[index - 1], index, command)) {
        ERROR(my_create_str("Client %zu command queue is full", index));
        FREE(command);
        return;
    }
    AL(FALSE, my_push_back, &server->client_list[index - 1]->command_queue,
        command, STRING);
    if (my_str_contains(command, "\n"))
        server->poll_fds[index].events |= POLLOUT;
}

static void read_unauthenticated_client_action(server_t *server, size_t index)
{
    size_t read_size = 0;
    char *team_name = NULL;

    if (ioctl(server->poll_fds[index].fd, FIONREAD, &read_size) < 0)
        THROW(my_create_str("EXCEPTION: ioctl failed: %s", STRERR));
    if (read_size == 0)
        return disconnect_client(server, index, team_name);
    team_name = AL(FALSE, my_calloc, read_size + 1, sizeof(char));
    if (read(server->poll_fds[index].fd, team_name, read_size) < 0)
        return disconnect_client(server, index, team_name);
    server->client_list[index - 1]->team_name = AL(FALSE, my_resize_alloc,
        server->client_list[index - 1]->team_name,
        my_strlen(server->client_list[index - 1]->team_name),
        my_strlen(team_name) + my_strlen(
        server->client_list[index - 1]->team_name) + 1 * sizeof(char));
    my_strcat(server->client_list[index - 1]->team_name, team_name);
    if (my_str_contains(team_name, "\n"))
        server->poll_fds[index].events |= POLLOUT;
    FREE(team_name);
}

void read_client_action(server_t *server, size_t index)
{
    if (server->client_list[index - 1]->is_authenticated)
        read_authenticated_client_action(server, index);
    else
        read_unauthenticated_client_action(server, index);
}
