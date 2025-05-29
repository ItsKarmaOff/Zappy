/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_compute_power_long_double function
*/
/**
 * @file my_compute_power_long_double.c
 * @brief The file containing the my_compute_power_long_double function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Returns the power (p) of the number (nb)
 * @note Returns 0 if the power is negative
 * @param nb The number to calculate
 * @param power The power of the number
 * @return <b>long double</b> The power of the number
 * @author Nicolas TORO
 */
long double my_compute_power_long_double(long double nb, long double p)
{
    long double result;

    if (p > 0.0L)
        result = nb * my_compute_power_long_double(nb, p - 1.0L);
    else if (p == 0.0L)
        result = 1.0L;
    else
        result = 0.0L;
    return result;
}
