/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The orientation.c
*/
/**
 * @file orientation.c
 * @brief The orientation.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

static bool check_orientation_args(char **args, orientation_t *orientation)
{
    size_t tmp_orientation = 0;

    tmp_orientation = my_get_number(args[2], DEFAULT_NB);
    if (my_errno != SUCCESS ||
    tmp_orientation < NORTH || tmp_orientation > WEST) {
        ERROR(my_create_str("Invalid orientation: %s", args[2]));
        return false;
    }
    *orientation = (orientation_t)tmp_orientation;
    return true;
}

static void update_orientation(
    server_t *server, player_t *player, orientation_t orientation)
{
    player->orientation = orientation;
    send_ppo_to_gui(server, NULL, player);
    printf("Player #%zu's set orientation to %s\n",
        player->id, orientation_names[orientation]);
}

void handle_server_command_orientation(
    server_t *server, UNUSED client_t *client, char **args)
{
    size_t player_id = 0;
    orientation_t orientation = 0;

    DEBUG("Executing \"Orientation\" command");
    if (my_array_len((void **)args) != 3) {
        ERROR("Invalid number of arguments for \"Orientation\" command");
        return;
    }
    player_id = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || player_id == 0
        || player_id >= server->game.game_settings.next_player_id) {
        ERROR(my_create_str("Invalid player ID: %s", args[1]));
        return;
    }
    if (!check_orientation_args(args, &orientation))
        return;
    update_orientation(server, get_player_by_id(&server->game, player_id),
        orientation);
}
