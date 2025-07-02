/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "pause" command for server clients
*/
/**
 * @file pause.c
 * @brief The file containing the handling of
 * the "pause" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
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
