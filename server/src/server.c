/*
** EPITECH PROJECT, 2025
** Project
** File description:
** The server.c
*/
/**
 * @file server.c
 * @brief The server.c
 * @author Nicolas TORO
 */

#include "server.h"

server_t *create_server(int argc, char **argv)
{
    server_t *server = my_calloc(1, sizeof(server_t));

    init_server_from_args(server, argc, argv);
    start_server(server);
    return server;
}

void run(server_t *server)
{
    DEBUG("Server is running\n");
    //while (true) {

    //}
}
