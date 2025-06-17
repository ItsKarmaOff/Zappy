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

#include "commands/commands_ai.h"
#include <math.h>

static size_t get_message_size(char **args)
{
    size_t size = 0;

    for (size_t i = 0; args[i] != NULL; i++) {
        size += strlen(args[i]) + 1;
    }
    return size;
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
    vector2u_t target_position, char *message)
{
    int dx = (int)target_position.x - (int)current_client->player->position.x;
    int dy = (int)target_position.y - (int)current_client->player->position.y;
    double angle = 0.0;

    if (dx == 0 && dy == 0) {
        message[8] = '0';
        return;
    }
    message[8] = (char)((int)((get_angle(server, current_client, dx, dy)
    + M_PI / 8.0) / (M_PI / 4.0)) % 8 + 1) + '0';
}

static void send_broadcast(server_t *server, client_t *client, char *message)
{
    client_t *current_client = NULL;

    for (size_t i = 0; i < server->current_clients_number; i++) {
        current_client = server->client_list[i];
        if (current_client == client
            || current_client->client_type != CLIENT_AI)
            continue;
        calculate_direction(server, current_client, client->player->position,
            message);
        dprintf(current_client->socket_fd, "%s", message);
    }
    send_pbc_to_gui(server, NULL, client->player, message + 8);
}

void handle_ai_command_broadcast(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    char message[sizeof("message K,\n") + get_message_size(args + 1) + 1];

    DEBUG("Executing \"Broadcast\" command");
    strcpy(message, "message K,");
    for (size_t i = 1; args[i] != NULL; i++) {
        strcat(message, " ");
        strcat(message, args[i]);
    }
    strcat(message, "\n");
    send_broadcast(server, client, message);
}
