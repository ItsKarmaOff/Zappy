/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The no_refill.c
*/
/**
 * @file no_refill.c
 * @brief The no_refill.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_no_refill(
    server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"No Refill\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"NoRefill\" command");
        return;
    }
    if (server->game.game_settings.no_refill == false) {
        server->game.game_settings.no_refill = true;
        printf(GREEN "No refill has been enabled." ENDL);
    } else {
        server->game.game_settings.no_refill = false;
        printf(RED "No refill has been disabled." ENDL);
    }
}
