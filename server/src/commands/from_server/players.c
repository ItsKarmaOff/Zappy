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

static void display_players(const game_t *game)
{
    player_t *player = NULL;

    for (size_t index = 0; index < game->game_settings.next_player_id;
    index++) {
        player = get_player_by_id(game, index);
        if (player == NULL)
            continue;
        printf(BOLD "- %zu:" RESET " %s [%s]",
            player->id, player->is_egg ? "Egg" : "Player",
            player->team->name);
        if (player->is_egg)
            printf(" (creator: %zi)\n", (player->creator_id == 0 ?
                -1 : (ssize_t)player->creator_id));
        else
            printf(" (position: (%zu, %zu) | level: %zu)\n",
                player->position.x, player->position.y, player->level);
    }
}

void handle_server_command_players(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Players\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Players\" command");
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Players Information:" ENDL);
    display_players(&server->game);
    my_putstr("========================================"
        "========================================\n");
}
