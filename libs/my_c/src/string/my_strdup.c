/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strdup function
*/
/**
 * @file my_strdup.c
 * @brief The file containing the my_strdup function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Duplicates a string (src) and returns the new string
 * @param src The string to duplicate
 * @return <b>char*</b> The duplicated string
 * @author Nicolas TORO
 */
char *my_strdup(char const *src)
{
    char *result;
    size_t len_src = my_strlen(src);

    if (src == NULL)
        return NULL;
    result = my_calloc(len_src + 1, sizeof(char));
    for (size_t i = 0; i < len_src; i++)
        result[i] = src[i];
    return result;
}
