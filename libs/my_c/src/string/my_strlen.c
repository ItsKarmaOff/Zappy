/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strlen function
*/
/**
 * @file my_strlen.c
 * @brief The file containing the my_strlen function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the length of a string (str)
 * @param str The string to check
 * @return <b>intmax_t</b> The length of the string
 * @author Nicolas TORO
 */
intmax_t my_strlen(char const *str)
{
    intmax_t len = 0;

    if (str == NULL)
        return 0;
    while (str[len] != '\0')
        len = len + 1;
    return len;
}
