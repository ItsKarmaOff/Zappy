/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strdup_word_array function
*/
/**
 * @file my_strdup_word_array.c
 * @brief The file containing the my_strdup_word_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Duplicates a word array (array) and returns the new array
 * @param array The word array to duplicate
 * @return <b>char**</b> The duplicated word array
 * @author Nicolas TORO
 */
char **my_strdup_word_array(char **array)
{
    char **new_array;
    size_t i = 0;

    if (array == NULL)
        return NULL;
    new_array = my_calloc(my_array_len((void **)array) + 1, sizeof(char *));
    for (; array[i] != NULL; i++)
        new_array[i] = my_strdup(array[i]);
    new_array[i] = NULL;
    return new_array;
}
