/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "extra_logs" option
*/
/**
 * @file extra_logs.c
 * @brief The file containing the function for the "extra_logs" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void option_extra_logs(UNUSED server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -e (or --extraLogs) option");
    my_strlowcase(parsing->argv[parsing->index + 1]);
    if (my_strcmp(parsing->argv[parsing->index + 1], "true") == 0)
        my_update_extra_logs(TRUE);
    else if (my_strcmp(parsing->argv[parsing->index + 1], "false") == 0)
        my_update_extra_logs(FALSE);
    else
        EXCEPTION("Invalid argument for -e (or --extraLogs) option, "
            "it must be 'true' or 'false'");
    parsing->index += 1;
}
