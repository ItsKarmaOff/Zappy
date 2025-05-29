/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_nbrlen function
*/
/**
 * @file my_nbrlen.c
 * @brief The file containing the my_nbrlen function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the length of a number (nb)
 * @param nb The number to check
 * @return <b>intmax_t</b> The length of the number
 * @author Nicolas TORO
 */
intmax_t my_nbrlen(intmax_t nb)
{
    int len = 0;

    if (nb == 0)
        return 1;
    if (nb < 0) {
        len++;
        nb = - nb;
    }
    while (nb > 0) {
        nb = nb / 10;
        len++;
    }
    return len;
}
