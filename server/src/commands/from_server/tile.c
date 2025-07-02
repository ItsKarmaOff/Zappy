/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "tile" command for server clients
*/
/**
 * @file tile.c
 * @brief The file containing the handling of
 * the "Tile" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

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

void handle_server_command_tile(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    vector2u_t position = {0, 0};

    DEBUG("Executing \"Tile\" command");
    if (my_array_len((void **)args) != 3) {
        ERROR("Invalid number of arguments for \"Tile\" command");
        return;
    }
    if (!check_position_args(&server->game, args, &position))
        return;
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Tile Information:" ENDL);
    display_tile(&server->game.map[position.y][position.x], "");
    my_putstr("========================================"
        "========================================\n");
}
