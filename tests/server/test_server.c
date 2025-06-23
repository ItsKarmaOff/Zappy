/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The server.c
*/
/**
 * @file server.c
 * @brief The server.c
 * @author Nicolas TORO
 */

#include "tests.h"
#include "server.h"

void close_server(void)
{
    my_exit(SUCCESS, GREEN "Server shutdown successfully." ENDL);
}

/* Example pour les fonctions qui exit */
Test(create_server1, test_create_server_with_no_args, .init = redirect_all_std, .exit_code = 84)
{
    create_server(1, (char *[]){"zappy_server"});
}

/* Example pour les fonctions classic */
Test(create_server2, test_create_server_with_good_args, .init = redirect_all_std, .fini = close_server, .exit_code = 0)
{
    create_server(12, (char *[]){"zappy_server", "-p", "4242", "-x", "10", "-y", "10", "-n", "team1", "team2", "-c", "1"});
}