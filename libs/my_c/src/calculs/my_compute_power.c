/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_compute_power function
*/
/**
 * @file my_compute_power.c
 * @brief The file containing the my_compute_power function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Returns the power (p) of the number (nb)
 * @note Returns 0 if the power is negative
 * @param nb The number to calculate
 * @param power The power of the number
 * @return <b>intmax_t</b> The power of the number
 * @author Nicolas TORO
 */
intmax_t my_compute_power(intmax_t nb, intmax_t p)
{
    intmax_t result;

    if (p > 0)
        result = nb * my_compute_power(nb, p - 1);
    else if (p == 0)
        result = 1;
    else
        result = 0;
    return result;
}
