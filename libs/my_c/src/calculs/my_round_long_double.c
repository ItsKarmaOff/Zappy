/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_round_long_double function
*/
/**
 * @file my_round_long_double.c
 * @brief The file containing the my_round_long_double function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Rounds a double to a certain precision
 * @param nb The number to round
 * @param precision The precision to round to
 * @return <b>long double</b> The rounded number
 * @author Nicolas TORO
 */
long double my_round_long_double(long double nb, long double precision)
{
    long double factor = my_compute_power_long_double(10.0L, precision);
    long double temp = nb * factor;
    long double rounded = (temp >= 0.0L) ? (temp + 0.5L) : (temp - 0.5L);
    long double integer = 0.0;

    modfl(rounded, &integer);
    return integer / factor;
}
