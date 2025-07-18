/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The server class implementation
*/
/**
 * @file server.c
 * @brief The server class implementation
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "server.h"

static void destroy_server(void *server)
{
    static server_t *server_ptr = NULL;

    if (server != NULL) {
        server_ptr = server;
        return;
    }
    DEBUG("Destroying server...");
    if (server_ptr == NULL)
        return;
    destroy_clients(server_ptr);
    destroy_game(&server_ptr->game);
}

static void handle_signal(UNUSED int signum)
{
    DEBUG("CTRL+C (or CTRL+D) received, shutting down server...");
    my_exit(SUCCESS, GREEN "Server shutdown successfully." ENDL);
}

static void display_shortcuts(const server_t *server, const char *ip_address)
{
    my_putstr(BOLD UNDERLINE "\nShortcuts:" ENDL);
    printf(BOLD "- Launch GUI:" RESET "\t\t./zappy_gui -h %s -p %d\n",
        ip_address ? ip_address : "127.0.0.1", server->port);
    printf(BOLD "- Launch GUI (debug):" RESET "\t(echo \"GRAPHIC\"; cat) | "
        "nc %s %d\n", ip_address ? ip_address : "127.0.0.1", server->port);
    printf(BOLD "- Launch AI:" RESET "\t\t./zappy_ai -h %s -p %d -n "
        "<team_name>\n", ip_address ? ip_address : "127.0.0.1", server->port);
    printf(BOLD "- Launch AI (debug):" RESET "\t(echo \"<team_name>\"; cat) | "
        "nc %s %d\n", ip_address ? ip_address : "127.0.0.1", server->port);
}

void display_server(const server_t *server, bool display_details)
{
    char *ip_address = get_ip_address();

    my_putstr("========================================"
        "========================================\n");
    my_putstr(BOLD UNDERLINE "Server Information:" ENDL);
    printf(BOLD "- Connection:" RESET " %s:%d\n", ip_address ?
        ip_address : "127.0.0.1", server->port);
    printf(BOLD "- Clients connected:" RESET " %zu\n\n",
        server->current_clients_number - 1);
    display_game(&server->game, display_details);
    if (display_details)
        display_shortcuts(server, ip_address);
    my_putstr("========================================"
        "========================================\n");
    FREE(ip_address);
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
    display_server(server, true);
    return server;
}

void run(server_t *server)
{
    int poll_count = 0;

    DEBUG("Server is running");
    while (true) {
        poll_count = poll(server->poll_fds,
            server->current_clients_number + 1, 0);
        if (poll_count < 0)
            THROW(my_create_str("EXCEPTION: Poll failed: %s", STRERR));
        for (size_t index = 0; index < server->current_clients_number + 1;
        index++)
            analyze_poll(server, index);
        execute_actions(server);
        update_game(server);
    }
}
