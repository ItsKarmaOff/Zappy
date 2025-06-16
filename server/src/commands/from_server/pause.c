/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The pause.c
*/
/**
 * @file pause.c
 * @brief The pause.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_pause(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Pause\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Pause\" command");
        return;
    }
    if (server->game.game_settings.is_paused == false) {
        server->game.game_settings.is_paused = true;
        printf(GREEN "Game has been paused." ENDL);
    } else {
        server->game.game_settings.is_paused = false;
        printf(RED "Game has been resumed." ENDL);
    }
}
