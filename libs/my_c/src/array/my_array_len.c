/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_array_len function
*/
/**
 * @file my_array_len.c
 * @brief The file containing the my_array_len function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the length of an array (array)
 * @param array The array to check
 * @return <b>size_t</b> The length of the array
 * @author Nicolas TORO
 */
size_t my_array_len(void **array)
{
    size_t len = 0;

    if (array == NULL)
        return 0;
    while (array[len] != NULL)
        len = len + 1;
    return len;
}
