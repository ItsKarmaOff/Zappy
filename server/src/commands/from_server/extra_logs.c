/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The extra_logs.c
*/
/**
 * @file extra_logs.c
 * @brief The extra_logs.c
 * @author Nicolas TORO
 */

#include "commands/commands_server.h"

void handle_command_extra_logs(UNUSED server_t *server, UNUSED client_t *client,
    char **args)
{
    if (my_array_len((void **) args) != 1) {
        ERROR("Invalid number of arguments for \"Extra Logs\" command\n");
        return;
    }
    if (extra_logs(NONE) == FALSE) {
        my_update_extra_logs(TRUE);
        my_putstr(GREEN "Extra logs enabled\n" RESET);
    } else {
        my_update_extra_logs(FALSE);
        my_putstr(RED "Extra logs disabled\n" RESET);
    }
}