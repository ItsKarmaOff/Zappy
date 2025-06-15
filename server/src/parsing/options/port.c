/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The port.c
*/
/**
 * @file port.c
 * @brief The port.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_port(server_t *server, parsing_t *parsing)
{
    if (parsing->argc <= parsing->index + 1)
        EXCEPTION("Missing argument for -p (or --port) option");
    server->port = my_get_number(
        parsing->argv[parsing->index + 1], DEFAULT_NB);
    if (my_errno != SUCCESS || server->port <= 0 || server->port > MAX_PORT)
        EXCEPTION("Invalid argument for -p (or --port) option, "
            "it must be a number between 1 and " MAX_PORT_STR "");
    parsing->index += 1;
}
