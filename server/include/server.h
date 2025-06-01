/*
** EPITECH PROJECT, 2025
** Project
** File description:
** The server.h
*/
/**
 * @file server.h
 * @brief The server.h
 * @author Nicolas TORO
 */

#ifndef SERVER_H_
    #define SERVER_H_

    #include "my.h"

typedef struct team_s {
    char *name;
    node_t *player_list;
} team_t;

typedef struct player_s {
    team_t *team;
} player_t;

typedef struct game_settings_s {
    int width; /* The width of the game map */
    int height; /* The height of the game map */
    size_t clients_per_team; /* The number of clients per team */
    int frequency; /* Reciprocal of time unit for execution of actions */
} game_settings_t;

typedef struct game_s {
    game_settings_t *game_settings; /* The settings of the game */
    node_t *team_list; /* The list of teams in the game */
} game_t;

typedef struct client_s {
    int socket_fd; /* The socket file descriptor */
    struct sockaddr_in address; /* The address of the client */
    node_t *command_queue; /* The queue of commands to execute */

    player_t *player; /* The associated player */
} client_t;

typedef struct server_s {
    int port; /* The port of the server */
    int socket_fd; /* The socket file descriptor */
    struct sockaddr_in address; /* The address of the server */
    socklen_t addr_len; /* The length of the address */

    struct pollfd *poll_fds; /* The poll file descriptors */
    size_t max_clients_number; /* The maximum number of clients */
    size_t current_clients_number; /* The current number of clients */
    node_t *client_list; /* The list of connected clients */

    game_t *game; /* The game structure */
} server_t;

#endif /* SERVER_H_ */
