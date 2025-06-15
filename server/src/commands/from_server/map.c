/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The map.c
*/
/**
 * @file map.c
 * @brief The map.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_map(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Map\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Map\" command");
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Map Information:" ENDL);
    printf(BOLD "- Map size:" RESET " %zu x %zu\n",
        server->game.game_settings.width, server->game.game_settings.height);
    my_putstr(BOLD "- Map content:" ENDL);
    for (size_t y = 0; y < server->game.game_settings.height; y++) {
        for (size_t x = 0; x < server->game.game_settings.width; x++)
            display_tile(&server->game.map[y][x], "    ");
    }
    my_putstr("========================================"
        "========================================\n");
}
