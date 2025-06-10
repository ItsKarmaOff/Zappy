/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_revstr function
*/
/**
 * @file my_revstr.c
 * @brief The file containing the my_revstr function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Reverses the characters in a string (str)
 * and returns the string (str)
 * @param str The string to reverse
 * @return <b>char*</b> The reversed string
 * @author Nicolas TORO
 */
char *my_revstr(char *str)
{
    int len = 0;
    char temp;

    while (str[len] != '\0')
        len = len + 1;
    for (size_t i = len / 2; i > 0; i--) {
        temp = str[i - 1];
        str[i - 1] = str[len - i];
        str[len - i] = temp;
    }
    return str;
}
