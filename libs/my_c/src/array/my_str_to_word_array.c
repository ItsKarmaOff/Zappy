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

static bool str_is_separator(const char *str, size_t index,
    separator_type_t type, const char *separator)
{
    switch (type) {
        case DEFAULT_SEPARATORS:
            if (my_char_is_alpha(str[index]) == 0
            && my_char_is_num(str[index]) == 0)
                return true;
            break;
        case CHAR_SEPARATORS:
            if (my_char_is(str[index], separator))
                return true;
            break;
        case STRING_SEPARATORS:
            if (my_strncmp(str + index, separator, my_strlen(separator)) == 0)
                return true;
            break;
    }
    return false;
}

size_t count_words(const char *str,
    separator_type_t type, const char *separator)
{
    size_t nb_words = 0;
    bool add_word = true;
    size_t len_separator = my_strlen(separator) - 1;

    for (size_t index = 0; str[index] != '\0'; index++) {
        if (!str_is_separator(str, index, type, separator) && add_word) {
            nb_words++;
            add_word = false;
        }
        if (str_is_separator(str, index, type, separator))
            add_word = true;
        if (add_word)
            index = ((type == STRING_SEPARATORS) ?
                index + len_separator : index);
    }
    return nb_words;
}

static void move_save(const char *str, size_t *saved_index,
    separator_type_t type, const char *separator)
{
    size_t len_separator = my_strlen(separator) - 1;

    for (; str[*saved_index] != '\0' &&
    str_is_separator(str, *saved_index, type, separator); (*saved_index)++)
        *saved_index = ((type == STRING_SEPARATORS) ?
            *saved_index + len_separator : *saved_index);
}

static size_t count_letters(const char *str, size_t *saved_index,
    separator_type_t type, const char *separator)
{
    size_t nb_letters = 0;

    for (size_t index = *saved_index; str[index] != '\0'
    && !str_is_separator(str, index, type, separator); index++)
        nb_letters++;
    *saved_index = *saved_index + nb_letters;
    return nb_letters;
}

/**
 * @brief Returns an array of words delimited
 * by a separator (separator) from a string (str)
 * @param str The string to convert
 * @param type The type of separator
 * @param separator The separator to use
 * @return <b>char**</b> The array of words
 * @author Nicolas TORO
 */
char **my_str_to_word_array(const char *str,
    separator_type_t type, const char *separator)
{
    size_t nb_words = count_words(str, type, separator);
    char **array = NULL;
    size_t saved_index = 0;
    size_t nb_letters = 0;

    if (nb_words == 0)
        return NULL;
    array = my_calloc(nb_words + 1, sizeof(char *));
    for (size_t index = 0; index < nb_words; index++) {
        move_save(str, &saved_index, type, separator);
        nb_letters = count_letters(str, &saved_index, type, separator);
        array[index] = my_strndup(str + saved_index - nb_letters, nb_letters);
    }
    return array;
}
