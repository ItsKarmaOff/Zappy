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

static void destroy_server(void *server)
{
    static server_t *server_ptr = NULL;

    if (server != NULL) {
        server_ptr = server;
        return;
    }
    DEBUG("Destroying server...\n");
    if (server_ptr == NULL)
        return;
    destroy_clients(server_ptr);
    destroy_game(&server_ptr->game);
}

static void handle_signal(UNUSED int signum)
{
    DEBUG("CTRL+C (or CTRL+D) received, shutting down server...\n");
    my_exit(SUCCESS, GREEN "Server shutdown successfully.\n" RESET);
}

server_t *create_server(int argc, char **argv)
{
    server_t *server = my_calloc(1, sizeof(server_t));

    srand(time(NULL));
    init_server_from_args(server, argc, argv);
    destroy_server(server);
    my_program_destroy(&destroy_server);
    start_server(server);
    signal(SIGINT, handle_signal);
    signal(SIGHUP, handle_signal);
    return server;
}

void run(server_t *server)
{
    int poll_count = 0;

    DEBUG("Server is running\n");
    while (true) {
        poll_count = poll(server->poll_fds,
            server->current_clients_number + 1, 0);
        if (poll_count < 0)
            THROW(my_create_str("EXCEPTION: Poll failed: %s\n", STRERR));
        for (size_t index = 0; index < server->current_clients_number + 1;
        index++)
            analyse_poll(server, index);
        execute_actions(server);
        update_game(server);
    }
}
