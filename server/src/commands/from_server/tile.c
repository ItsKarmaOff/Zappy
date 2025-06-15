/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The tile.c
*/
/**
 * @file tile.c
 * @brief The tile.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

static bool check_position_args(
    const game_t *game, char **args, vector2u_t *position)
{
    position->x = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || position->x >= game->game_settings.width) {
        ERROR(my_create_str("Invalid position x: %s\n", args[1]));
        return false;
    }
    position->y = my_get_number(args[2], DEFAULT_NB);
    if (my_errno != SUCCESS || position->y >= game->game_settings.height) {
        ERROR(my_create_str("Invalid position y: %s\n", args[2]));
        return false;
    }
    return true;
}

void handle_server_command_tile(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    vector2u_t position = {0, 0};

    DEBUG("Executing \"Tile\" command\n");
    if (my_array_len((void **)args) != 3) {
        ERROR("Invalid number of arguments for \"Tile\" command\n");
        return;
    }
    if (!check_position_args(&server->game, args, &position))
        return;
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Tile Information:\n" RESET);
    display_tile(&server->game.map[position.y][position.x], "");
    my_putstr("========================================"
        "========================================\n");
}
