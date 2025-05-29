/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_isinf_double function
*/
/**
 * @file my_isinf_double.c
 * @brief The file containing the my_isinf_double function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Check if the number is inf
 * @param nb The number to check
 * @return <b>bool</b> <u>True</u> if the number is inf, <u>False</u> otherwise
 * @author Nicolas TORO
 */
bool my_isinf_double(double nb)
{
    return nb == 1.0 / 0.0 || nb == -1.0 / 0.0;
}
