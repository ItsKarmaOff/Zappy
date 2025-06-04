/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strndup function
*/
/**
 * @file my_strndup.c
 * @brief The file containing the my_strndup function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Duplicates a string (src) with a defined size (n)
 * and returns the new string
 * @param src The string to duplicate
 * @param n The size of the string
 * @return <b>char*</b> The duplicated string
 * @author Nicolas TORO
 */
char *my_strndup(char const *src, size_t n)
{
    char *dest = my_calloc(n + 1, sizeof(char *));

    if (src == NULL)
        return NULL;
    for (size_t i = 0; src[i] != '\0' && i < n; i++)
        dest[i] = src[i];
    return dest;
}
