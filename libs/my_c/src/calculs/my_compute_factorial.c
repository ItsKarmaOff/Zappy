/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_compute_factorial function
*/
/**
 * @file my_compute_factorial.c
 * @brief The file containing the my_compute_factorial function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Returns the factorial of a number (nb)
 * @note Returns 0 if the number is negative or greater than 12
 * @param nb The number to calculate
 * @return <b>intmax_t</b> The factorial of the number
 * @author Nicolas TORO
 */
intmax_t my_compute_factorial(intmax_t nb)
{
    if (nb == 0 || nb == 1)
        return 1;
    else if (nb > 1 && nb < 13)
        return nb * my_compute_factorial(nb - 1);
    else
        return 0;
}
