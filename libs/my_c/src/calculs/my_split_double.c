/*
** EPITECH PROJECT, 2024
** my_libs
** File description:
** The my_split_double.c
*/
/**
 * @file my_split_double.c
 * @brief The my_split_double.c
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Split a double into an integer part and a decimal part
 * @param value The value to split
 * @param integer_part The integer part
 * @return <b>double</b> The decimal part
 */
double my_split_double(double value, double *integer_part)
{
    *integer_part = my_round_double(value, 0);
    return value - *integer_part;
}
