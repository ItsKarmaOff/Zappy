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
 * @return <b>int</b> The length of the word array
 * @author Nicolas TORO
 */
int my_word_array_len(char **array, int nb_str)
{
    int len = 0;

    if (array == NULL)
        return 0;
    for (int i = 0; i < nb_str; i++)
        len += my_strlen(array[i]);
    return len;
}
