/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_word_array_to_str function
*/
/**
 * @file my_word_array_to_str.c
 * @brief The file containing the my_word_array_to_str function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Converts an array of words to a string
 * @param word_array The array of words to convert
 * @param separator The separator to use between words
 * @return <b>char *</b> The string containing the words
 */
char *my_word_array_to_str(char **word_array, const char *separator)
{
    char *str = NULL;

    if (word_array == NULL || word_array[0] == NULL)
        return NULL;
    str = my_calloc(WORD_ARRAY_LEN(word_array) +
        my_array_len((void **)word_array), sizeof(char));
    for (size_t i = 0; word_array[i] != NULL; i++) {
        my_strcat(str, word_array[i]);
        if (word_array[i + 1] != NULL)
            my_strcat(str, separator);
    }
    return str;
}
