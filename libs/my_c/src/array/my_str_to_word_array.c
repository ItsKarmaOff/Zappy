/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_str_to_word_array function
*/
/**
 * @file my_str_to_word_array.c
 * @brief The file containing the my_str_to_word_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static bool is_separator(char *str, int64_t index,
    char *separator, separator_type_t type)
{
    switch (type) {
        case DEFAULT_SEPARATOR:
            if (my_char_is_alpha(str[index]) == 0
            && my_char_is_num(str[index]) == 0)
                return true;
            break;
        case LIST_SEPARATOR:
            if (my_char_is(str[index], separator))
                return true;
            break;
        case STRING_SEPARATOR:
            if (my_strncmp(str + index, separator, my_strlen(separator)) == 0)
                return true;
            break;
    }
    return false;
}

int64_t count_words(char *str, char *separator, separator_type_t type)
{
    int64_t nb_words = 0;
    bool add_word = true;
    int64_t len_separator = my_strlen(separator) - 1;

    for (int64_t index = 0; str[index] != '\0'; index++) {
        if (!is_separator(str, index, separator, type) && add_word) {
            nb_words++;
            add_word = false;
        }
        if (is_separator(str, index, separator, type))
            add_word = true;
        if (add_word)
            index = ((type == STRING_SEPARATOR) ?
                index + len_separator : index);
    }
    return nb_words;
}

static void move_save(char *str, int64_t *saved_index,
    char *separator, separator_type_t type)
{
    int64_t len_separator = my_strlen(separator) - 1;

    for (; str[*saved_index] != '\0' &&
    is_separator(str, *saved_index, separator, type); (*saved_index)++)
        *saved_index = ((type == STRING_SEPARATOR) ?
            *saved_index + len_separator : *saved_index);
}

int64_t count_letters(char *str, int64_t *saved_index,
    char *separator, separator_type_t type)
{
    int64_t nb_letters = 0;

    for (int64_t index = *saved_index; str[index] != '\0'
    && !is_separator(str, index, separator, type); index++)
        nb_letters++;
    *saved_index = *saved_index + nb_letters;
    return nb_letters;
}

/**
 * @brief Returns an array of words delimited
 * by a separator (separator) from a string (str)
 * @param str The string to convert
 * @param separator The separator to use
 * @param type The type of separator
 * @return <b>char**</b> The array of words
 * @author Nicolas TORO
 */
char **my_str_to_word_array(char *str, char *separator, separator_type_t type)
{
    int64_t nb_words = count_words(str, separator, type);
    char **array = my_malloc(sizeof(char *) * (nb_words + 1));
    int64_t saved_index = 0;
    int64_t nb_letters = 0;

    for (int64_t index = 0; index < nb_words; index++) {
        move_save(str, &saved_index, separator, type);
        nb_letters = count_letters(str, &saved_index, separator, type);
        array[index] = my_strndup(str + saved_index - nb_letters, nb_letters);
    }
    array[nb_words] = NULL;
    return array;
}
