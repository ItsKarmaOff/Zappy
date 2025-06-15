/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The tp.c
*/
/**
 * @file tp.c
 * @brief The tp.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

static bool check_position_args(
    const game_t *game, char **args, vector2u_t *position)
{
    position->x = my_get_number(args[2], DEFAULT_NB);
    if (my_errno != SUCCESS || position->x >= game->game_settings.width) {
        ERROR(my_create_str("Invalid position x: %s", args[2]));
        return false;
    }
    position->y = my_get_number(args[3], DEFAULT_NB);
    if (my_errno != SUCCESS || position->y >= game->game_settings.height) {
        ERROR(my_create_str("Invalid position y: %s", args[3]));
        return false;
    }
    return true;
}

static void update_position(
    server_t *server, player_t *player, vector2u_t position)
{
    player->position = position;
    send_plv_to_gui(server, NULL, player);
    printf("Teleport player #%zu's to (%zu, %zu)\n",
        player->id, position.x, position.y);
}

void handle_server_command_tp(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    size_t player_id = 0;
    vector2u_t position = {0, 0};

    DEBUG("Executing \"Tp\" command");
    if (my_array_len((void **)args) != 4) {
        ERROR("Invalid number of arguments for \"Tp\" command");
        return;
    }
    player_id = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || player_id == 0
        || player_id >= server->game.game_settings.next_player_id) {
        ERROR(my_create_str("Invalid player ID: %s", args[1]));
        return;
    }
    if (!check_position_args(&server->game, args, &position))
        return;
    update_position(server, get_player_by_id(&server->game, player_id),
        position);
}
