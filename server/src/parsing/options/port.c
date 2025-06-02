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

void option_port(server_t *server,
    int argc, char **argv, size_t *index)
{
    if ((size_t)argc <= *index + 1)
        EXCEPTION("Missing argument for -p (or --port) option\n");
    server->port = my_get_number(argv[*index + 1], DEFAULT_NB);
    if (my_errno != SUCCESS || server->port <= 0 || server->port > MAX_PORT)
        EXCEPTION("Invalid argument for -p (or --port) option, "
            "it must be a number between 1 and " MAX_PORT_STR "\n");
    *index += 1;
}
