/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the handling of
** the "debug_mode" command for server clients
*/
/**
 * @file debug_mode.c
 * @brief The file containing the handling of
 * the "debug_mode" command for server clients
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "commands/commands_server.h"

void handle_server_command_debug_mode(
    UNUSED server_t *server, UNUSED client_t *client, char **args)
{
    DEBUG("Executing \"Debug Mode\" command");
    if (my_array_len((void **) args) != 1) {
        ERROR("Invalid number of arguments for \"Debug Mode\" command");
        return;
    }
    if (debug_mode(NONE) == FALSE) {
        my_update_debug_mode(TRUE);
        my_putstr(GREEN "Debug mode enabled" ENDL);
    } else {
        my_update_debug_mode(FALSE);
        my_putstr(RED "Debug mode disabled" ENDL);
    }
}
