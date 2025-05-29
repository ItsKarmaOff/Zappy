/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_get_last_char function
*/
/**
 * @file my_get_last_char.c
 * @brief The file containing the my_get_last_char function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the last char of a string (str)
 * @param str The string to check
 * @return <b>char</b> The last char of the string
 * @author Nicolas TORO
 */
char my_get_last_char(char *str)
{
    int index = 0;

    if (str == NULL || str[0] == '\0')
        return '\0';
    for (; str[index] != '\0'; index++);
    return str[index - 1];
}
