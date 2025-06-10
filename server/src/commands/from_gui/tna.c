/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The tna.c
*/
/**
 * @file tna.c
 * @brief The tna.c
 * @author Nicolas TORO
 */

#include "commands/gui.h"

void handle_command_tna(UNUSED server_t *server, UNUSED client_t *client,
    UNUSED char **args)
{
    DEBUG("Executing \"tna\" command\n");
    if (my_array_len((void **)args) != 1) {
        DEBUG("Invalid number of arguments for \"tna\" command\n");
        send_sbp_to_gui(server, client);
        return;
    }
    for (size_t index = 0; index < server->game.game_settings.teams_number;
    index++)
        send_tna_to_gui(server, client, server->game.team_list[index]);
}
