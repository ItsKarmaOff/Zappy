/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The player.c
*/
/**
 * @file player.c
 * @brief The player.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_player(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    size_t player_id = 0;

    DEBUG("Executing \"Player\" command");
    if (my_array_len((void **)args) != 2) {
        ERROR("Invalid number of arguments for \"Player\" command");
        return;
    }
    player_id = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || player_id == 0
    || player_id >= server->game.game_settings.next_player_id
    || get_player_by_id(&server->game, player_id) == NULL) {
        ERROR(my_create_str("Invalid player ID: %s", args[1]));
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Player Information:" ENDL);
    display_player(get_player_by_id(&server->game, player_id), "");
    my_putstr("========================================"
        "========================================\n");
}
