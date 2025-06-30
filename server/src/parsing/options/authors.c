/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the function for the "authors" option
*/
/**
 * @file authors.c
 * @brief The file containing the function for the "authors" option
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "parsing.h"

void option_authors(UNUSED server_t *server, UNUSED parsing_t *parsing)
{
    my_putstr(BOLD "AUTHORS:" ENDL
        ITALIC "\t- Students of EPITECH Nice 2025 -" ENDL
        "\tChristophe VANDEVOIR\n"
        "\tGianni TUERO\n"
        "\tLou PELLEGRINO\n"
        "\tNicolas TORO\n"
        "\tOlivier POUECH\n"
        "\tRaphaël LAUNAY\n");
    my_exit(SUCCESS, "");
}
