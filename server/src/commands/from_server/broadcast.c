/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of
** the "broadcast" command for server clients
*/
/**
 * @file broadcast.c
 * @brief The file containing the handling of
 * the "broadcast" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"
#include <math.h>

static bool check_position_args(
    const game_t *game, char **args, vector2u_t *position)
{
    position->x = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || position->x >= game->game_settings.width) {
        ERROR(my_create_str("Invalid position x: %s", args[1]));
        return false;
    }
    position->y = my_get_number(args[2], DEFAULT_NB);
    if (my_errno != SUCCESS || position->y >= game->game_settings.height) {
        ERROR(my_create_str("Invalid position y: %s", args[2]));
        return false;
    }
    return true;
}

static vector2s_t get_shortest_vector(server_t *server,
    vector2s_t *sender, vector2s_t *receiver)
{
    vector2s_t new_receiver = {0, 0};

    if (ABS(sender->x - receiver->x) <=
        (ssize_t)server->game.game_settings.width / 2)
        new_receiver.x = receiver->x;
    else
        new_receiver.x = -
            (ssize_t)server->game.game_settings.width - receiver->x;
    if (ABS(sender->y - receiver->y) <=
        (ssize_t)server->game.game_settings.height / 2)
        new_receiver.y = receiver->y;
    else
        new_receiver.y = -
            (ssize_t)server->game.game_settings.height - receiver->y;
    return new_receiver;
}

static ssize_t calculate_direction(server_t *server,
    vector2s_t *sender, vector2s_t *receiver, orientation_t orientation)
{
    vector2s_t new_receiver = get_shortest_vector(server, sender, receiver);

    if (sender->x == new_receiver.x && sender->y < new_receiver.y)
        return (UP_CENTER + 2 * (orientation - 1) - 1) % 8 + 1;
    if (sender->x < new_receiver.x && sender->y < new_receiver.y)
        return (UP_LEFT + 2 * (orientation - 1) - 1) % 8 + 1;
    if (sender->x < new_receiver.x && sender->y == new_receiver.y)
        return (LEFT_CENTER + 2 * (orientation - 1) - 1) % 8 + 1;
    if (sender->x < new_receiver.x && sender->y > new_receiver.y)
        return (DOWN_LEFT + 2 * (orientation - 1) - 1) % 8 + 1;
    if (sender->x == new_receiver.x && sender->y > new_receiver.y)
        return (DOWN_CENTER + 2 * (orientation - 1) - 1) % 8 + 1;
    if (sender->x > new_receiver.x && sender->y > new_receiver.y)
        return (DOWN_RIGHT + 2 * (orientation - 1) - 1) % 8 + 1;
    if (sender->x > new_receiver.x && sender->y == new_receiver.y)
        return (RIGHT_CENTER + 2 * (orientation - 1) - 1) % 8 + 1;
    if (sender->x > new_receiver.x && sender->y < new_receiver.y)
        return (UP_RIGHT + 2 * (orientation - 1) - 1) % 8 + 1;
    return SAME;
}

static void send_broadcast(
    server_t *server, vector2u_t *position, char *message)
{
    client_t *current_client = NULL;

    for (size_t i = 0; i < server->current_clients_number; i++) {
        current_client = server->client_list[i];
        if (current_client->client_type != CLIENT_AI)
            continue;
        message[8] = (char)calculate_direction(server,
            (vector2s_t *) position,
            (vector2s_t *) &current_client->player->position,
            current_client->player->orientation) + '0';
        dprintf(current_client->socket_fd, "%s", message);
    }
    send_pbc_to_gui(server, NULL, NULL,
        message + my_strlen(BROADCAST_MESSAGE_PREFIX));
}

void handle_server_command_broadcast(
    server_t *server, UNUSED client_t *client, char **args)
{
    char message[sizeof("message K, \n") + my_strlen(args[1])];
    vector2u_t position = {0, 0};

    DEBUG("Executing \"Broadcast\" command");
    if (my_array_len((void **) args) != 4) {
        ERROR("Invalid number of arguments for \"Broadcast\" command");
        return;
    }
    if (!check_position_args(&server->game, args, &position))
        return;
    my_memset(message, 0, sizeof(message));
    my_strcpy(message, BROADCAST_MESSAGE_PREFIX);
    my_strcat(message, args[3]);
    my_strcat(message, "\n");
    send_broadcast(server, &position, message);
}
