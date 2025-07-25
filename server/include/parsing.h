/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the parsing functions
*/
/**
 * @file parsing.h
 * @brief The file containing the parsing functions
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#ifndef PARSING_H_
    #define PARSING_H_

    #include "server_data_structures.h"
    #include "game.h"



/* Options types and structures */

/**
 * @struct parsing_s
 * @brief Represents the parsing context for program arguments
 */
typedef struct parsing_s {
    /** The number of program arguments */
    size_t argc;
    /** The program arguments */
    char **argv;
    /** The current index in the program arguments */
    size_t index;

    /** The options found in the program arguments */
    uint8_t options_found;
    /** The list of team names */
    node_t *team_name_list;
} parsing_t;

/**
 * @enum option_type_e
 * @brief Represents the type of an option
 */
typedef enum option_type_e {
    NOT_REQUIRED = 0, ///< The option is not required
    PORT_OPTION = 1 << 0, ///< The option is a port option
    WIDTH_OPTION = 1 << 1, ///< The option is a width option
    HEIGHT_OPTION = 1 << 2, ///< The option is a height option
    NAMES_OPTION = 1 << 3, ///< The option is a names option
    CLIENTS_OPTION = 1 << 4, ///< The option is a clients option
    META_OPTION = 1 << 5, ///< The option is a meta option
} option_type_t;

/**
 * @struct option_t
 * @brief Represents a program option
 */
typedef struct option_s {
    /** The short name of the option */
    const char short_name;
    /** The long name of the option */
    const char *long_name;
    /** The data associated with the option */
    const char *data;
    /** The description of the option */
    const char *description;
    /** The type of the option */
    option_type_t type;
    /** The function to call for the option */
    void (*function)(server_t *server, parsing_t *parsing);
} option_t;

/**
 * @brief The array of argument functions
 */
extern const option_t options[];



/* Options functions */

/**
 * @biref Display the authors of the project
 * @param server The server instance
 * @param parsing The parsing context containing program arguments
 * @throw SUCCESS If the authors are displayed successfully
 */
void option_authors(server_t *server, parsing_t *parsing);

/**
 * @biref Set the auto end option of the game
 * @param server The server instance to set the auto end for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_auto_end(server_t *server, parsing_t *parsing);

/**
 * @biref Set the number of clients per team of the game
 * @param server The server instance to set the number of clients for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_clients(server_t *server, parsing_t *parsing);

/**
 * @biref Set whether to enable debug mode for debugging purposes
 * @param server The server instance to set the debug mode for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_debug_mode(server_t *server, parsing_t *parsing);

/**
 * @biref Set whether to enable extra logs for debugging purposes
 * @param server The server instance to set the extra logs for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_extra_logs(server_t *server, parsing_t *parsing);

/**
 * @biref Set the frequency of the game
 * @param server The server instance to set the frequency for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_frequency(server_t *server, parsing_t *parsing);

/**
 * @biref Set the height of the map
 * @param server The server instance to set the height for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_height(server_t *server, parsing_t *parsing);

/**
 * @biref Display the help message for the program
 * @param server The server instance
 * @param parsing The parsing context containing program arguments
 * @throw SUCCESS If the help message is displayed successfully
 */
void option_help(server_t *server, parsing_t *parsing);

/**
 * @biref Set whether to enable infinite food for the game
 * @param server The server instance to set the infinite food for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_infinite_food(server_t *server, parsing_t *parsing);

/**
 * @biref Set the names of the teams for the game
 * @param server The server instance to set the names of the teams for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_names(server_t *server, parsing_t *parsing);

/**
 * @biref Set whether to enable no refill for the game
 * @param server The server instance to set the infinite food for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_no_refill(server_t *server, parsing_t *parsing);

/**
 * @biref Set the port of the server
 * @param server The server instance to set the port for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_port(server_t *server, parsing_t *parsing);

/**
 * @biref Set whether to show eggs in the game
 * @param server The server instance to set the show eggs for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_show_eggs(server_t *server, parsing_t *parsing);

/**
 * @biref Display the version of the program
 * @param server The server instance
 * @param parsing The parsing context containing program arguments
 * @throw SUCCESS If the version is displayed successfully
 */
void option_version(server_t *server, parsing_t *parsing);

/**
 * @biref Set the width of the map
 * @param server The server instance to set the width for
 * @param parsing The parsing context containing program arguments
 * @throw FAILURE If the argument is invalid or missing
 */
void option_width(server_t *server, parsing_t *parsing);



/* Global functions */

/**
 * @brief Initializes the server from command line arguments
 * @param server The server instance to initialize
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @throw FAILURE If the server initialization fails
 */
void init_server_from_args(server_t *server, int argc, char **argv);

#endif /* PARSING_H_ */
