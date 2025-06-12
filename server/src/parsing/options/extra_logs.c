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

#include "parsing.h"

void option_extra_logs(UNUSED server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -e (or --extraLogs) option\n");
    my_strlowcase(parsing->argv[parsing->index + 1]);
    if (my_strcmp(parsing->argv[parsing->index + 1], "true") == 0)
        my_update_extra_logs(TRUE);
    else if (my_strcmp(parsing->argv[parsing->index + 1], "false") == 0)
        my_update_extra_logs(FALSE);
    else
        EXCEPTION("Invalid argument for -e (or --extraLogs) option, "
            "it must be 'true' or 'false'\n");
    parsing->index += 1;
}
