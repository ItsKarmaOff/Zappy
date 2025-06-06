/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The server_data_structures.h
*/
/**
 * @file server_data_structures.h
 * @brief The server_data_structures.h
 * @author Nicolas TORO
 */

#ifndef SERVER_DATA_STRUCTURES_H_
    #define SERVER_DATA_STRUCTURES_H_

    #include "server_macros.h"

/* Server Enums */

typedef enum orientation_e {
    NORTH = 1, /* The player is facing north */
    EAST = 2, /* The player is facing east */
    SOUTH = 3, /* The player is facing south */
    WEST = 4, /* The player is facing west */
} orientation_t;

/* Forward declarations of structures */

typedef struct team_s team_t;
typedef struct client_s client_t;
typedef struct server_s server_t;

/* Structures */

typedef struct player_s {
    size_t id; /* The ID of the player */
    bool is_egg; /* Whether the player is an egg */
    size_t creator_id; /* The ID of the player who created the egg */
    vector2u_t position; /* The position of the player on the map */
    orientation_t orientation; /* The orientation of the player */
    team_t *team; /* The team of the player */
} player_t;

typedef struct team_s {
    const char *name; /* The name of the team */
    node_t *player_list; /* The list of players in the team */
} team_t;

typedef struct game_settings_s {
    size_t width; /* The width of the game map */
    size_t height; /* The height of the game map */
    size_t teams_number; /* The number of teams */
    size_t start_clients_per_team; /* The number of clients per team */
    size_t frequency; /* Reciprocal of time unit for execution of actions */
    size_t next_player_id; /* The next player ID to be assigned */
} game_settings_t;

typedef struct game_s {
    game_settings_t game_settings; /* The settings of the game */
    team_t **team_list; /* The list of teams in the game */
} game_t;


typedef struct action_s {
    /* The arguments of the action */
    char **action_args;
    /* The time to wait before executing the action */
    double time_to_wait;
    /* The action to execute */
    void (*cmd_function)(server_t *, client_t *, char **);
} action_t;

typedef struct client_s {
    int socket_fd; /* The socket file descriptor */
    sockaddr_in_t address; /* The address of the client */
    node_t *command_queue; /* The queue of commands to execute */
    action_t next_action; /* The next action to execute */
    bool is_gui; /* Whether the client is a GUI client */

    player_t *player; /* The associated player */

    time_t last_action_time; /* The time of the last action */
} client_t;

typedef struct server_s {
    int port; /* The port of the server */
    int socket_fd; /* The socket file descriptor */
    sockaddr_in_t address; /* The address of the server */
    socklen_t addr_len; /* The length of the address */

    pollfd_t *poll_fds; /* The poll file descriptors */
    size_t max_clients_number; /* The maximum number of clients */
    size_t current_clients_number; /* The current number of clients */
    client_t **client_list; /* The list of connected clients */

    game_t game; /* The game structure */
} server_t;


typedef struct command_s {
    /* The command to execute */
    const char *command;
    /* The time to wait before executing the command */
    double time_to_wait;
    /* The function to execute the command */
    void (*cmd_function)(server_t *, client_t *, char **);
} command_t;

extern const command_t commands_ai[];
extern const command_t commands_gui[];

#endif /* SERVER_DATA_STRUCTURES_H_ */
