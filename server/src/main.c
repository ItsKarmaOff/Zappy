/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The main function of the server
*/
/**
 * @file main.c
 * @brief The main function of the server
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "server.h"

int main(int argc, char **argv)
{
    server_t *server = NULL;

    my_update_malloc(TRUE);
    server = create_server(argc, argv);
    run(server);
    my_free();
    return SUCCESS;
}
