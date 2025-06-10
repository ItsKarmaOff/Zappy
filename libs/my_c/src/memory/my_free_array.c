/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_free_array function
*/
/**
 * @file my_free_array.c
 * @brief The file containing the my_free_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Frees an array (array)
 * @param array The array to free
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_free_array(void **array)
{
    if (array == NULL)
        return;
    for (size_t i = 0; array[i] != NULL; i++)
        FREE(array[i]);
    FREE(array);
}
