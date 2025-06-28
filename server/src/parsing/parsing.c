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

/// Letters used : p, x, y, n, c, f, s, e, i, r, d, l, h, v, a

const option_t options[] = {
    {'p', "port", "\tport",
        "\tThe port of the server",
        PORT_OPTION, &option_port},
    {'x', "width", "\twidth",
        "\tThe width of the world",
        WIDTH_OPTION, &option_width},
    {'y', "height", "\theight",
        "\tThe height of the world",
        HEIGHT_OPTION, &option_height},
    {'n', "names", "\tname1 name2 ...",
        "The names of the teams",
        NAMES_OPTION, &option_names},
    {'c', "clients", "\tclientsNumber",
        "The number of clients per team",
        CLIENTS_OPTION, &option_clients},
    {'f', "frequency", "\tfrequency",
        "The reciprocal of time unit for execution of action "
        "(default: 100)",
        NOT_REQUIRED, &option_frequency},
    {'s', "showEggs", GREEN "\ttrue" RESET "|" RED "false" RESET,
        "Show eggs in the game "
        "(default: " RED "false" RESET ")",
        NOT_REQUIRED, &option_show_eggs},
    {'e', "autoEnd", GREEN "\ttrue" RESET "|" RED "false" RESET,
        "Automatically end the game when only one team remains "
        "(default: " RED "false" RESET ")",
        NOT_REQUIRED, &option_auto_end},
    {'i', "infiniteFood", GREEN "true" RESET "|" RED "false" RESET,
        "Enable infinite food for players "
        "(default: " RED "false" RESET ")",
        NOT_REQUIRED, &option_infinite_food},
    {'r', "noRefill", GREEN "\ttrue" RESET "|" RED "false" RESET,
        "Disable resource refill on tiles "
        "(default: " RED "false" RESET ")",
        NOT_REQUIRED, &option_no_refill},
    {'d', "debugMode", GREEN "\ttrue" RESET "|" RED "false" RESET,
        "Enable debug mode for debugging purposes "
        "(default: " GREEN "true" RESET ")",
        NOT_REQUIRED, &option_debug_mode},
    {'l', "extraLogs", GREEN "\ttrue" RESET "|" RED "false" RESET,
        "Enable extra logs for debugging purposes "
        "(default: " RED "false" RESET ")",
        NOT_REQUIRED, &option_extra_logs},
    {'H', "help", "\t\t",
        "Display this help message",
        META_OPTION, &option_help},
    {'V', "version", "\t\t",
        "Display the version of the server",
        META_OPTION, &option_version},
    {'A', "authors", "\t\t",
        "Display the authors of the project",
        META_OPTION, &option_authors},
    {0, NULL, NULL, NULL, NOT_REQUIRED, NULL}
};

static bool is_valid_short_option(parsing_t *parsing, size_t option_index)
{
    if (my_strlen(parsing->argv[parsing->index]) == 2
    && parsing->argv[parsing->index][0] == '-'
    && parsing->argv[parsing->index][1] == options[option_index].short_name)
        return true;
    return false;
}

static bool is_valid_long_option(parsing_t *parsing, size_t option_index)
{
    if (my_strlen(parsing->argv[parsing->index]) > 2
    && parsing->argv[parsing->index][0] == '-'
    && parsing->argv[parsing->index][1] == '-'
    && my_strcmp(parsing->argv[parsing->index] + 2,
    options[option_index].long_name) == 0)
        return true;
    return false;
}

static void analyse_arg(server_t *server, parsing_t *parsing)
{
    for (size_t option_index = 0; options[option_index].short_name != 0;
    option_index++) {
        if (is_valid_short_option(parsing, option_index)) {
            options[option_index].function(server, parsing);
            parsing->options_found |= options[option_index].type;
            return;
        }
        if (is_valid_long_option(parsing, option_index)) {
            options[option_index].function(server, parsing);
            parsing->options_found |= options[option_index].type;
            return;
        }
    }
    THROW(my_create_str("EXCEPTION: Invalid options: \"%s\"\n"
        "Please use -H or --help to see the list of available options.",
        parsing->argv[parsing->index]));
}

static void missing_options(uint8_t options_found)
{
    for (size_t option_index = 0; options[option_index].short_name != 0;
    option_index++) {
        if (options[option_index].type != NOT_REQUIRED &&
        (options_found & options[option_index].type) == 0) {
            THROW(my_create_str("EXCEPTION: Missing option: -%c or --%s",
                options[option_index].short_name,
                options[option_index].long_name));
        }
    }
}

void init_server_from_args(server_t *server, int argc, char **argv)
{
    parsing_t parsing = {0};
    size_t team_index = 0;

    parsing.argc = argc;
    parsing.argv = argv;
    server->game.game_settings.frequency = DEFAULT_FREQUENCY;
    server->game.game_settings.next_player_id = 1;
    for (parsing.index = 1; parsing.index < parsing.argc; parsing.index++)
        analyse_arg(server, &parsing);
    if (parsing.options_found != (PORT_OPTION | WIDTH_OPTION | HEIGHT_OPTION |
    NAMES_OPTION | CLIENTS_OPTION))
        missing_options(parsing.options_found);
    create_game_map(server, &server->game);
    for (node_t *tmp = parsing.team_name_list; tmp != NULL; tmp = tmp->next) {
        server->game.team_list[team_index] =
            create_team(&server->game, tmp->data);
        team_index++;
    }
}
