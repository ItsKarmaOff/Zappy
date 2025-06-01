/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The parsing.c
*/
/**
 * @file parsing.c
 * @brief The parsing.c
 * @author Nicolas TORO
 */

#include "parsing.h"

const option_t options[] = {
    {'p', "port", "port",
        "The port of the server",
        PORT_OPTION, NULL},
    {'x', "width", "width",
        "The width of the world",
        WIDTH_OPTION, NULL},
    {'y', "height", "height",
        "The height of the world",
        HEIGHT_OPTION, NULL},
    {'n', "names", "name1 name2 ...",
        "The names of the teams",
        NAMES_OPTION, NULL},
    {'c', "clients", "clientsNb",
        "The number of clients per team",
        CLIENTS_OPTION, NULL},
    {'f', "frequency", "frequency",
        "The reciprocal of time unit for execution of action",
        FREQUENCY_OPTION, NULL},
    {'h', "help", "",
        "Display this help message",
        NOT_REQUIRED, NULL},
    {'v', "version", "",
        "Display the version of the server",
        NOT_REQUIRED, NULL},
    {'a', "authors", "",
        "Display the authors of the project",
        NOT_REQUIRED, NULL},
    {0, NULL, NULL, NULL, NOT_REQUIRED, NULL}
};

static void analyse_arg(server_t *server, int argc, char **argv, int *index)
{
    for (size_t option_index = 0; options[option_index].short_name != 0;
    option_index++) {
        if (my_strlen(argv[*index]) == 2 && argv[*index][0] == '-'
        && argv[*index][1] == options[option_index].short_name) {
            options[option_index].function(server, argc, argv, index);
            server->options_found |= options[option_index].type;
            return;
        }
        if (my_strlen(argv[*index]) > 2
        && argv[*index][0] == '-' && argv[*index][1] == '-'
        && my_strcmp(argv[*index] + 2, options[option_index].long_name) == 0) {
            options[option_index].function(server, argc, argv, index);
            server->options_found |= options[option_index].type;
            return;
        }
    }
    THROW(my_create_str("EXCEPTION: Invalid argument: %s\n", argv[*index]));
}

static void missing_options(uint32_t options_found)
{
    for (size_t option_index = 0; options[option_index].short_name != 0;
    option_index++) {
        if (options[option_index].type != NOT_REQUIRED &&
        (options_found & options[option_index].type) == 0) {
            THROW(my_create_str("EXCEPTION: Missing option: -%c or --%s\n",
                options[option_index].short_name,
                options[option_index].long_name));
        }
    }
}

void init_server_from_args(server_t *server, int argc, char **argv)
{
    server->game = my_calloc(1, sizeof(game_t));
    for (int index = 1; index < argc; index++) {
        analyse_arg(server, argc, argv, &index);
    }
    if (server->options_found != (PORT_OPTION | WIDTH_OPTION | HEIGHT_OPTION |
    NAMES_OPTION | CLIENTS_OPTION | FREQUENCY_OPTION))
        missing_options(server->options_found);
}
