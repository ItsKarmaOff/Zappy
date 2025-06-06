/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The authors.c
*/
/**
 * @file authors.c
 * @brief The authors.c
 * @author Nicolas TORO
 */

#include "parsing.h"

void option_authors(UNUSED server_t *server, UNUSED parsing_t *parsing)
{
    my_putstr(BOLD "AUTHORS:\n" RESET
        "\tChristophe VANDEVOIR\n"
        "\tGianni TUERO\n"
        "\tLou PELLEGRINO\n"
        "\tNicolas TORO\n"
        "\tOlivier POUECH\n"
        "\tRaphaël LAUNAY\n");
    my_exit(SUCCESS, "");
}
