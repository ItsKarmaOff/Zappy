/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strlowcase function
*/
/**
 * @file my_strlowcase.c
 * @brief The file containing the my_strlowcase function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Replaces upcase by lowcase of a string (str)
 * @param str The string to modify
 * @return <b>char*</b> The modified string
 * @author Nicolas TORO
 */
char *my_strlowcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 65 && str[i] <= 90)
            str[i] = str[i] + 32;
    }
    return str;
}
