/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_word_array_len function
*/
/**
 * @file my_word_array_len.c
 * @brief The file containing the my_word_array_len function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the length of an word array (array)
 * @param array The array to check
 * @param nb_str The number of strings in the array
 * @return <b>size_t</b> The length of the word array
 * @author Nicolas TORO
 */
size_t my_word_array_len(char **array, size_t nb_str)
{
    size_t len = 0;

    if (array == NULL)
        return 0;
    for (size_t i = 0; i < nb_str; i++)
        len += my_strlen(array[i]);
    return len;
}
