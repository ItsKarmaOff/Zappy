/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The fork.c
*/
/**
 * @file fork.c
 * @brief The fork.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_server_command_fork(
    UNUSED server_t *server, UNUSED client_t *client, UNUSED char **args)
{
    player_t *new_player = NULL;
    size_t team_index = 0;
    team_t *team = NULL;

    DEBUG("Executing \"Fork\" command");
    if (my_array_len((void **)args) != 2) {
        ERROR("Invalid number of arguments for \"Fork\" command");
        return;
    }
    team_index = my_get_number(args[1], DEFAULT_NB);
    if (my_errno != SUCCESS || team_index == 0
    || team_index > server->game.game_settings.teams_number) {
        ERROR(my_create_str("Invalid team index: %s", args[1]));
        return;
    }
    team = server->game.team_list[team_index];
    new_player = create_player(&server->game, team);
    AL(FALSE, my_push_back, &team->player_list, new_player, VOID);
    send_enw_to_gui(server, NULL, new_player);
}
