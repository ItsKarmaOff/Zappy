/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_isnan_double function
*/
/**
 * @file my_isnan_double.c
 * @brief The file containing the my_isnan_double function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Check if the number is NaN
 * @param nb The number to check
 * @return <b>bool</b> <u>True</u> if the number is NaN, <u>False</u> otherwise
 * @author Nicolas TORO
 */
bool my_isnan_double(double nb)
{
    return nb != nb;
}
