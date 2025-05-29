/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_compute_power_double function
*/
/**
 * @file my_compute_power_double.c
 * @brief The file containing the my_compute_power_double function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Returns the power (p) of the number (nb)
 * @note Returns 0 if the power is negative
 * @param nb The number to calculate
 * @param power The power of the number
 * @return <b>double</b> The power of the number
 * @author Nicolas TORO
 */
double my_compute_power_double(double nb, double p)
{
    double result;

    if (p > 0.0)
        result = nb * my_compute_power_double(nb, p - 1.0);
    else if (p == 0.0)
        result = 1.0;
    else
        result = 0.0;
    return result;
}
