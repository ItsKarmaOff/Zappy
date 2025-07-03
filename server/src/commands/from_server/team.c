/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of the "team" command for server clients
*/
/**
 * @file team.c
 * @brief The file containing the handling of
 * the "team" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_team(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    size_t team_id = 0;

    DEBUG("Executing \"Team\" command");
    if (my_array_len((void **)args) != 2) {
        ERROR("Invalid number of arguments for \"Team\" command");
        return;
    }
    team_id = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || team_id == 0 ||
    team_id >= server->game.game_settings.teams_number) {
        ERROR(my_create_str("Invalid team ID: %s", args[1]));
        return;
    }
    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Team Information:" ENDL);
    display_team(server->game.team_list[team_id], "");
    my_putstr("========================================"
        "========================================\n");
}
