/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The broadcast.c
*/
/**
 * @file broadcast.c
 * @brief The broadcast.c
 * @author Nicolas TORO
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

static double get_angle(server_t *server, client_t *current_client,
    int dx, int dy)
{
    double angle = 0.0;

    if (dx > (int)server->game.game_settings.width / 2)
        dx -= (int)server->game.game_settings.width;
    if (dx < -(int)server->game.game_settings.width / 2)
        dx += (int)server->game.game_settings.width;
    if (dy > (int)server->game.game_settings.height / 2)
        dy -= (int)server->game.game_settings.height;
    if (dy < -(int)server->game.game_settings.height / 2)
        dy += (int)server->game.game_settings.height;
    angle = atan2(dx, - dy)
        - ((current_client->player->orientation - 1) * M_PI) / 2.0;
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}

static void calculate_direction(server_t *server, client_t *current_client,
    vector2u_t *target_position, char *message)
{
    int dx = (int)target_position->x - (int)current_client->player->position.x;
    int dy = (int)target_position->y - (int)current_client->player->position.y;
    double angle = 0.0;

    if (dx == 0 && dy == 0) {
        message[8] = '0';
        return;
    }
    message[8] = (char)((int)((get_angle(server, current_client, dx, dy)
        + M_PI / 8.0) / (M_PI / 4.0)) % 8 + 1) + '0';
}

static void send_broadcast(
    server_t *server, vector2u_t *position, char *message)
{
    client_t *current_client = NULL;

    for (size_t i = 0; i < server->current_clients_number; i++) {
        current_client = server->client_list[i];
        if (current_client->client_type != CLIENT_AI)
            continue;
        calculate_direction(server, current_client, position,
            message);
        dprintf(current_client->socket_fd, "%s", message);
    }
    send_pbc_to_gui(server, NULL, NULL, message + 8);
}

void handle_server_command_broadcast(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
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
    my_strcpy(message, "message K, ");
    my_strcat(message, args[3]);
    my_strcat(message, "\n");
    send_broadcast(server, &position, message);
}
