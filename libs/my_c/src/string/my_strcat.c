/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strcat function
*/
/**
 * @file my_strcat.c
 * @brief The file containing the my_strcat function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Concatenates two strings (dest) and (src)
 * @note The destination string must be allocated and have enough space
 * @param dest The destination string
 * @param src The source string
 * @return <b>char*</b> The destination string
 * @author Nicolas TORO
 */
char *my_strcat(char *dest, char const *src)
{
    int len_dest = my_strlen(dest);
    int len_src = my_strlen(src);
    int i = 0;

    if (dest == NULL || src == NULL)
        return NULL;
    for (i = 0; i < len_src; i++)
        dest[len_dest + i] = src[i];
    dest[len_dest + i] = '\0';
    return dest;
}
