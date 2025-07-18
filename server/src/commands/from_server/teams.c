/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "teams" command for server clients
*/
/**
 * @file teams.c
 * @brief The file containing the handling of
 * the "teams" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_teams(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    DEBUG("Executing \"Teams\" command");
    if (my_array_len((void **)args) != 1) {
        ERROR("Invalid number of arguments for \"Teams\" command");
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Teams Information:" ENDL);
    for (size_t index = 1; index < server->game.game_settings.teams_number;
    index++)
        printf(BOLD "- %zu:" RESET " %s (%zu players including %zu eggs)\n",
            index, server->game.team_list[index]->name,
            my_list_size(server->game.team_list[index]->player_list),
            server->game.team_list[index]->eggs_number);
    my_putstr("========================================"
        "========================================\n");
}
