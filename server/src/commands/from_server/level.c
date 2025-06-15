/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The level.c
*/
/**
 * @file level.c
 * @brief The level.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

static bool check_level_args(char **args, size_t *level)
{
    *level = my_get_number(args[2], DEFAULT_NB);
    if (my_errno != SUCCESS || *level > MAX_PLAYER_LEVEL) {
        ERROR(my_create_str("Invalid level: %s", args[2]));
        return false;
    }
    return true;
}

static void update_level(server_t *server, player_t *player, size_t level)
{
    player->level = level;
    send_plv_to_gui(server, NULL, player);
    printf("Player #%zu's set to level %zu\n", player->id, level);
}

void handle_server_command_level(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    size_t player_id = 0;
    size_t level = 0;

    DEBUG("Executing \"Level\" command");
    if (my_array_len((void **)args) != 3) {
        ERROR("Invalid number of arguments for \"Level\" command");
        return;
    }
    player_id = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || player_id == 0
    || player_id >= server->game.game_settings.next_player_id
    || get_player_by_id(&server->game, player_id) == NULL) {
        ERROR(my_create_str("Invalid player ID: %s", args[1]));
        return;
    }
    if (!check_level_args(args, &level))
        return;
    update_level(server, get_player_by_id(&server->game, player_id), level);
}
