/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strncpy function
*/
/**
 * @file my_strncpy.c
 * @brief The file containing the my_strncpy function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Copies a string (src) and paste it on another string (dest)
 * with a defined size (n)
 * @note The destination string must be allocated
 * @param dest The destination string
 * @param src The source string
 * @param n The size of the string
 * @return <b>char*</b> The destination string
 * @author Nicolas TORO
 */
char *my_strncpy(char *dest, char const *src, int n)
{
    int len = my_strlen(src);

    for (int i = 0; i < n; i++)
        dest[i] = src[i];
    if (len < n)
        dest[len] = '\0';
    return dest;
}
