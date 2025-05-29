/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_find_prime_sup function
*/
/**
 * @file my_find_prime_sup.c
 * @brief The file containing the my_find_prime_sup function
 * @author Nicolas TORO
*/

#include "../../include/my.h"

/**
 * @brief Returns the next prime number after a number (nb)
 * @param nb The number to check
 * @return <b>intmax_t</b> The next prime number after the number
 * or the number if it is prime
 * @author Nicolas TORO
 */
intmax_t my_find_prime_sup(intmax_t nb)
{
    intmax_t i = 0;

    if (nb <= 1)
        return 2;
    while (my_is_prime(nb + i) == 0)
        i++;
    return nb + i;
}
