/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_compute_square_root function
*/
/**
 * @file my_compute_square_root.c
 * @brief The file containing the my_compute_square_root function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Returns the square root of a number (nb)
 * @param nb The number to calculate
 * @return <b>intmax_t</b> The square root of the number
 * @author Nicolas TORO
 */
intmax_t my_compute_square_root(intmax_t nb)
{
    intmax_t i = 1;

    if (nb == 0)
        return 0;
    while (i * i <= nb) {
        if (nb / i == i
            && nb % i == 0) {
            return i;
        }
        i++;
    }
    return 0;
}
