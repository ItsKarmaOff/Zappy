/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strcpy function
*/
/**
 * @file my_strcpy.c
 * @brief The file containing the my_strcpy function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Copies a string (src) and paste it on another string (dest)
 * @note The destination string must be allocated
 * @param dest The destination string
 * @param src The source string
 * @param n The size of the string
 * @return <b>char*</b> The destination string
 * @author Nicolas TORO
 */
char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i = i + 1;
    }
    dest[i] = '\0';
    return dest;
}
