/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "debug_mode" option
*/
/**
 * @file debug_mode.c
 * @brief The file containing the function for the "debug_mode" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void option_debug_mode(UNUSED server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -d (or --debugMode) option");
    my_strlowcase(parsing->argv[parsing->index + 1]);
    if (my_strcmp(parsing->argv[parsing->index + 1], "true") == 0)
        my_update_debug_mode(TRUE);
    else if (my_strcmp(parsing->argv[parsing->index + 1], "false") == 0)
        my_update_debug_mode(FALSE);
    else
        EXCEPTION("Invalid argument for -d (or --debugMode) option, "
            "it must be 'true' or 'false'");
    parsing->index += 1;
}
