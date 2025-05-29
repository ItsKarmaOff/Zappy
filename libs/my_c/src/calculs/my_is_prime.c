/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_is_prime function
*/
/**
 * @file my_is_prime.c
 * @brief The file containing the my_is_prime function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns 1 if the number (nb) is prime and 0 otherwise
 * @param nb The number to check
 * @return <b>bool</b> <u>1</u> if the number is prime, <u>0</u> otherwise
 * @author Nicolas TORO
 */
bool my_is_prime(intmax_t nb)
{
    if (nb <= 1 || nb == 4)
        return 0;
    for (intmax_t i = 2; i < nb / 2; i++) {
        if (nb % i == 0)
            return 0;
    }
    return 1;
}
