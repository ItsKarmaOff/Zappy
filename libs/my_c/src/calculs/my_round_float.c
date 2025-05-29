/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_round_float function
*/
/**
 * @file my_round_float.c
 * @brief The file containing the my_round_float function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Rounds a double to a certain precision
 * @param nb The number to round
 * @param precision The precision to round to
 * @return <b>float</b> The rounded number
 * @author Nicolas TORO
 */
float my_round_float(float nb, float precision)
{
    float factor = my_compute_power_float(10.0f, precision);
    float temp = nb * factor;
    float rounded = (temp >= 0.0f) ? (temp + 0.5f) : (temp - 0.5f);
    float integer = 0.0f;

    modff(rounded, &integer);
    return integer / factor;
}
