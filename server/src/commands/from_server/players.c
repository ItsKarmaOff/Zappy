/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The players.c
*/
/**
 * @file players.c
 * @brief The players.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_players(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    player_t *player = NULL;

    DEBUG("Executing \"Players\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Players\" command");
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Players Information:" ENDL);
    for (size_t i = 0; i < server->game.game_settings.next_player_id; i++) {
        player = get_player_by_id(&server->game, i);
        if (player != NULL)
            display_player(player, "    ");
    }
    my_putstr("========================================"
        "========================================\n");
}
