/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of
** the "extra_logs" command for server clients
*/
/**
 * @file extra_logs.c
 * @brief The file containing the handling of
 * the "extra_logs" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_extra_logs(
    UNUSED server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"Extra Logs\" command");
    if (my_array_len((void **) args) != 1) {
        ERROR("Invalid number of arguments for \"Extra Logs\" command");
        return;
    }
    if (extra_logs(NONE) == FALSE) {
        my_update_extra_logs(TRUE);
        my_putstr(GREEN "Extra logs enabled" ENDL);
    } else {
        my_update_extra_logs(FALSE);
        my_putstr(RED "Extra logs disabled" ENDL);
    }
}
