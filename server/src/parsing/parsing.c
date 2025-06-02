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
        "\tThe port of the server",
        PORT_OPTION, &option_port},
    {'x', "width", "width",
        "\tThe width of the world",
        WIDTH_OPTION, &option_width},
    {'y', "height", "height",
        "\tThe height of the world",
        HEIGHT_OPTION, &option_height},
    {'n', "names", "name1 name2 ...",
        "The names of the teams",
        NAMES_OPTION, &option_names},
    {'c', "clients", "clientsNb",
        "The number of clients per team",
        CLIENTS_OPTION, &option_clients},
    {'f', "frequency", "frequency",
        "The reciprocal of time unit for execution of action",
        FREQUENCY_OPTION, &option_frequency},
    {'h', "help", "",
        "\tDisplay this help message",
        NOT_REQUIRED, &option_help},
    {'v', "version", "",
        "\tDisplay the version of the server",
        NOT_REQUIRED, &option_version},
    {'a', "authors", "",
        "\tDisplay the authors of the project",
        NOT_REQUIRED, &option_authors},
    {0, NULL, NULL, NULL, NOT_REQUIRED, NULL}
};

static void analyse_arg(server_t *server, int argc, char **argv, size_t *index)
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
    for (size_t index = 1; index < (size_t)argc; index++) {
        analyse_arg(server, argc, argv, &index);
    }
    if (server->options_found != (PORT_OPTION | WIDTH_OPTION | HEIGHT_OPTION |
    NAMES_OPTION | CLIENTS_OPTION | FREQUENCY_OPTION))
        missing_options(server->options_found);
}
