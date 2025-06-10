/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_add_chr function
*/
/**
 * @file my_add_chr.c
 * @brief The file containing the my_add_chr function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Adds a char (chr) at the end of a string (str)
 * @note The string must be allocated and have enough space
 * @param str The string to modify
 * @param chr The char to add
 * @return <b>char *</b> The modified string
 * @author Nicolas TORO
 */
char *my_add_chr(char *str, char chr)
{
    size_t index = 0;

    for (; str[index] != '\0'; index++);
    str[index] = chr;
    str[index + 1] = '\0';
    return str;
}
