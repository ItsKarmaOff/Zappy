/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The help.c
*/
/**
 * @file help.c
 * @brief The help.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_help(UNUSED server_t *server, UNUSED parsing_t *parsing)
{
    printf(BOLD "USAGE:" ENDL "\t%s "
        "-p port -x width -y height -n team1 team2 ... -c clientsNb\n\n"
        BOLD "DESCRIPTION:" ENDL, parsing->argv[0]);
    for (size_t i = 0; options[i].short_name != 0; i++) {
        printf("\t-%c, --%s\t%s\t\t%s\n",
            options[i].short_name, options[i].long_name,
            options[i].data, options[i].description);
    }
    my_exit(SUCCESS, "");
}
