/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_find_prime_inf function
*/
/**
 * @file my_find_prime_inf.c
 * @brief The file containing the my_find_prime_inf function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
* @brief Returns the previous prime number before a number (nb)
* @param nb The number to check
* @return <b>intmax_t</b> The previous prime number before the number
* or the number if it is prime
* @author Nicolas TORO
*/
intmax_t my_find_prime_inf(intmax_t nb)
{
    intmax_t i = 0;

    if (nb <= 1)
        return -1;
    while (my_is_prime(nb - i) == 0)
        i++;
    return nb - i;
}
