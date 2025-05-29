/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_compute_power_float function
*/
/**
 * @file my_compute_power_float.c
 * @brief The file containing the my_compute_power_float function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Returns the power (p) of the number (nb)
 * @note Returns 0 if the power is negative
 * @param nb The number to calculate
 * @param power The power of the number
 * @return <b>float</b> The power of the number
 * @author Nicolas TORO
 */
float my_compute_power_float(float nb, float p)
{
    float result;

    if (p > 0.0f)
        result = nb * my_compute_power_float(nb, p - 1.0f);
    else if (p == 0.0f)
        result = 1.0f;
    else
        result = 0.0f;
    return result;
}
