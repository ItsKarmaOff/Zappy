/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strncat function
*/
/**
 * @file my_strncat.c
 * @brief The file containing the my_strncat function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Concatenates two strings (dest) and (src) with a defined size (nb)
 * @note The destination string must be allocated and have enough space
 * @param dest The destination string
 * @param src The source string
 * @param nb The size of the string
 * @return <b>char*</b> The destination string
 * @author Nicolas TORO
 */
char *my_strncat(char *dest, char const *src, int n)
{
    int len_dest = my_strlen(dest);
    int i = 0;

    if (dest == NULL || src == NULL)
        return NULL;
    for (i = 0; i < n; i++)
        dest[len_dest + i] = src[i];
    dest[len_dest + i] = '\0';
    return dest;
}
