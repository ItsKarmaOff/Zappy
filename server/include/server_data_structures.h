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

/* Server data structures */



    /* Server Enums */

/**
 * @enum orientation_e
 * @brief The orientation of the player
 */
typedef enum orientation_e {
    NORTH = 1, ///< The player is facing north
    EAST = 2, ///< The player is facing east
    SOUTH = 3, ///< The player is facing south
    WEST = 4, ///< The player is facing west
} orientation_t;

/**
 * @enum resources_e
 * @brief The resources available in the game
 */
typedef enum resources_e {
    FOOD = 0, ///< The food resource
    LINEMATE = 1, ///< The linemate resource
    DERAUMERE = 2, ///< The deraumere resource
    SIBUR = 3, ///< The sibur resource
    MENDIANE = 4, ///< The mendiane resource
    PHIRAS = 5, ///< The phiras resource
    THYSTAME = 6, ///< The thystame resource
    RESOURCES_SIZE = 7 ///< The total number of resources
} resources_t;

/**
 * @enum client_type_e
 * @brief The type of client connected to the server
 */
typedef enum client_type_e {
    CLIENT_AI = 0, ///< The client is an AI client
    CLIENT_GUI = 1, ///< The client is a GUI client
    CLIENT_SERVER = 2 ///< The client is the server itself
} client_type_t;



    /* Forward declarations of structures */

typedef struct player_s player_t;
typedef struct team_s team_t;
typedef struct quantity_s quantity_t;
typedef struct game_settings_s game_settings_t;
typedef struct game_s game_t;
typedef struct action_s action_t;
typedef struct command_s command_t;
typedef struct client_s client_t;
typedef struct server_s server_t;



    /* Game structures */

/**
 * @struct player_s
 * @brief A structure representing a player in the game
 */
typedef struct player_s {
    /** The ID of the player */
    size_t id;
    /** Whether the player is an egg */
    bool is_egg;
    /** The ID of the player who created the egg */
    size_t creator_id;

    /** The position of the player on the map */
    vector2u_t position;
    /** The orientation of the player */
    orientation_t orientation;

    /** The level of the player */
    size_t level;
    /** The last time the player ate */
    time_t last_eat_time;
    /** The inventory of the player */
    size_t inventory[RESOURCES_SIZE];

    /** The team of the player */
    team_t *team;
    /** The associated client */
    client_t *client;
} player_t;

/**
 * @struct team_s
 * @brief A structure representing a team in the game
 */
typedef struct team_s {
    /** The name of the team */
    const char *name;
    /** The number of eggs in the team */
    size_t eggs_number;
    /** The list of players in the team */
    node_t *player_list;
} team_t;

/**
 * @struct quantity_s
 * @brief A structure representing the quantity of a resource in the game
 */
typedef struct quantity_s {
    /** The maximum number of items */
    size_t max_quantity;
    /** The current number of items */
    size_t current_quantity;
} quantity_t;

/**
 * @struct game_settings_s
 * @brief A structure representing the settings of the game
 */
typedef struct game_settings_s {
    /** The width of the game map */
    size_t width;
    /** The height of the game map */
    size_t height;

    /** Whether the game should end when only one team remains */
    bool auto_end;
    /** Whether the game should display the eggs */
    bool display_eggs;

    /** The number of teams */
    size_t teams_number;
    /** The number of clients per team */
    size_t start_clients_per_team;

    /** Reciprocal of time unit for execution of actions */
    size_t frequency;
    /** The next player ID to be assigned */
    size_t next_player_id;
} game_settings_t;

/**
 * @struct tile_s
 * @brief A structure representing a tile on the game map
 */
typedef struct tile_s {
    /** The position of the tile on the map */
    vector2u_t position;
    /** The number of resources on the tile */
    size_t resources[RESOURCES_SIZE];
} tile_t;

/**
 * @struct game_s
 * @brief A structure representing the game
 */
typedef struct game_s {
    /** The settings of the game */
    game_settings_t game_settings;
    /** The list of teams in the game */
    team_t **team_list;

    /** The map of the game */
    tile_t **map;
    /** The quantities of resources in the game */
    quantity_t resources[RESOURCES_SIZE];
    /** The last time resources were refilled */
    time_t last_refill_time;
    /** The team name of the winner */
    const char *winner_team_name;
} game_t;



    /* Commands and actions structures */

/**
 * @struct action_s
 * @brief A structure representing an action to be executed by a client
 */
typedef struct action_s {
    /** The arguments of the action */
    char **action_args;
    /** The time to wait before executing the action */
    double time_to_wait;
    /** The action to execute */
    void (*cmd_function)(server_t *, client_t *, char **);
} action_t;

/**
 * @struct command_s
 * @brief A structure representing a command to be executed by a client
 */
typedef struct command_s {
    /** The command to execute */
    const char *command;
    /** The time to wait before executing the command */
    double time_to_wait;
    /** The function to execute the command */
    void (*cmd_function)(server_t *, client_t *, char **);
} command_t;



    /* Client and server structures */

/**
 * @struct client_s
 * @brief A structure representing a client connected to the server
 */
typedef struct client_s {
    /** The socket file descriptor */
    int socket_fd;
    /** The address of the client */
    sockaddr_in_t address;

    /** Whether the client is authenticated */
    bool is_authenticated;
    /** The name of the team the client is trying to join */
    char *team_name;

    /** The type of client */
    client_type_t client_type;
    /** The associated player */
    player_t *player;

    /** The queue of commands to execute */
    node_t *command_queue;
    /** The next action to execute */
    action_t next_action;
    /** The time of the last action */
    time_t last_action_time;
} client_t;

/**
 * @struct server_s
 * @brief A structure representing the server
 */
typedef struct server_s {
    /** The port of the server */
    int port;
    /** The socket file descriptor */
    int socket_fd;
    /** The address of the server */
    sockaddr_in_t address;
    /** The length of the address */
    socklen_t addr_len;

    /** The list of poll file descriptors for current clients */
    pollfd_t *poll_fds;
    /** The current number of clients */
    size_t current_clients_number;
    /** The list of connected clients */
    client_t **client_list;

    /** The game structure */
    game_t game;
} server_t;



   /* Server commands arrays */

/**
 * @brief The array of AI commands
 */
extern const command_t commands_ai[];
/**
 * @brief The array of GUI commands
 */
extern const command_t commands_gui[];
/**
 * @brief The array of SERVER commands
 */
extern const command_t commands_server[];
/**
 * @brief The array of commands for the server
 */
extern const command_t *commands[];



    /* Resources arrays */

/**
 * @brief The names of the resources in the game
 */
extern const char *resources_names[RESOURCES_SIZE];
/**
 * @brief The density of each resource in the game
 */
extern const double resources_densities[RESOURCES_SIZE];



    /* Orientation arrays */

extern const char *orientation_names[];

#endif /* SERVER_DATA_STRUCTURES_H_ */
