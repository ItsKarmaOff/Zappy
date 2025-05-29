/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strupcase function
*/
/**
 * @file my_strupcase.c
 * @brief The file containing the my_strupcase function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Replaces lowcase by upcase of a string (str)
 * @param str The string to modify
 * @return <b>char*</b> The modified string
 * @author Nicolas TORO
 */
char *my_strupcase(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 97 && str[i] <= 122)
            str[i] = str[i] - 32;
    }
    return str;
}
