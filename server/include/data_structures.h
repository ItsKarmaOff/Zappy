/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The data_structures.h
*/
/**
 * @file data_structures.h
 * @brief The data_structures.h
 * @author Nicolas TORO
 */

#ifndef DATA_STRUCTURES_H_
    #define DATA_STRUCTURES_H_

    #include "my.h"



    /* Server macros */

    /* The maximum port number */
    #define MAX_PORT 65535

    /* The maximum port number as a string */
    #define MAX_PORT_STR "65535"

    /* The name of the graphic team */
    #define GRAPHIC_TEAM_NAME "GRAPHIC"

    /* The welcome message sent to clients */
    #define WELCOME_MESSAGE "WELCOME\n"

    /* The message sent to clients when an action is valid */
    #define VALID_AI "ok\n"

    /* The message sent to clients when an action is not valid */
    #define WRONG_AI "ko\n"

    /* The message sent to clients when the GUI is not valid */
    #define WRONG_GUI "suc\n"

    /**
     * @brief The message sent to clients
     * when the arguments of a command are invalid
     */
    #define INVALID_ARGS "sbp\n"



typedef struct egg_s {
    size_t id;
} egg_t;


typedef enum orientation_e {
    NORTH = 1, /* The player is facing north */
    EAST = 2, /* The player is facing east */
    SOUTH = 3, /* The player is facing south */
    WEST = 4, /* The player is facing west */
} orientation_t;

typedef struct team_s team_t;

typedef struct player_s {
    size_t id; /* The ID of the player */
    vector2u_t position; /* The position of the player on the map */
    orientation_t orientation; /* The orientation of the player */
    team_t *team; /* The team of the player */
} player_t;

typedef struct team_s {
    const char *name;
    player_t **player_list;
} team_t;

typedef struct game_settings_s {
    size_t width; /* The width of the game map */
    size_t height; /* The height of the game map */
    size_t teams_number; /* The maximum number of teams */
    size_t clients_per_team; /* The number of clients per team */
    size_t frequency; /* Reciprocal of time unit for execution of actions */
    size_t next_player_id; /* The next player ID to be assigned */
    size_t next_egg_id; /* The next egg ID to be assigned */
} game_settings_t;

typedef struct game_s {
    game_settings_t game_settings; /* The settings of the game */
    team_t **team_list; /* The list of teams in the game */
} game_t;

typedef struct client_s {
    int socket_fd; /* The socket file descriptor */
    sockaddr_in_t address; /* The address of the client */
    node_t *command_queue; /* The queue of commands to execute */
    bool is_gui; /* Whether the client is a GUI client */

    player_t *player; /* The associated player */

    size_t time_to_wait; /* The time to wait before the next action */
    struct timespec last_action_time; /* The time of the last action */
} client_t;

typedef struct server_s {
    uint32_t options_found; /* The options found in the program arguments */

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
    /* Whether the command is for GUI clients */
    bool is_gui;
    /* The function to execute the command */
    void (*cmd_function)(server_t *, client_t *, char **);
} command_t;

extern const command_t commands[];

#endif /* DATA_STRUCTURES_H_ */
