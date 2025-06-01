/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The parsing.h
*/
/**
 * @file parsing.h
 * @brief The parsing.h
 * @author Nicolas TORO
 */

#ifndef PARSING_H_
    #define PARSING_H_

    #include "data_structures.h"

typedef enum option_type_e {
    NOT_REQUIRED = 0, /* The option is not required */
    PORT_OPTION = 1 << 0, /* The option is a port option */
    WIDTH_OPTION = 1 << 1, /* The option is a width option */
    HEIGHT_OPTION = 1 << 2, /* The option is a height option */
    NAMES_OPTION = 1 << 3, /* The option is a names option */
    CLIENTS_OPTION = 1 << 4, /* The option is a clients option */
    FREQUENCY_OPTION = 1 << 5, /* The option is a frequency option */
} option_type_t;

/**
 * @struct option_t
 * @brief Represents a program option
 */
typedef struct option_s {
    const char short_name; /* The short name of the option */
    const char *long_name; /* The long name of the option */
    const char *data; /* The data associated with the option */
    const char *description; /* The description of the option */
    option_type_t type; /* The type of the option */
    void (*function)(server_t *server, int argc, char **argv, int *index);
    /* The function to call for the option */
} option_t;

extern const option_t options[]; /* The array of argument functions */

/**
 * @brief Initializes the server from command line arguments
 * @param server The server instance to initialize
 * @param argc The number of command line arguments
 * @param argv The command line arguments
 * @throw FAILURE If the server initialization fails
 */
void init_server_from_args(server_t *server, int argc, char **argv);

#endif /* PARSING_H_ */
