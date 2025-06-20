/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_str_to_array function
*/
/**
 * @file my_str_to_array.c
 * @brief The file containing the my_str_to_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static bool is_inhibitor(str_to_array_t *data, size_t index)
{
    if (my_char_is(data->str[index],
    data->settings.inhibitors_single) == true
    || my_char_is(data->str[index],
    data->settings.inhibitors_double) == true)
        return true;
    return false;
}

static bool is_default_separator(str_to_array_t *data, size_t index)
{
    if (my_char_is_alpha(data->str[index]) == 0
    && my_char_is_num(data->str[index]) == 0)
        return true;
    return false;
}

static bool is_char_separator(str_to_array_t *data, size_t index)
{
    if (my_char_is(data->str[index], data->settings.separator))
        return true;
    return false;
}

static bool is_string_separator(str_to_array_t *data, size_t index)
{
    if (data->settings.separator == NULL)
        return false;
    for (size_t i = 0; ((char **)data->settings.separator)[i] != NULL; i++) {
        if (my_strncmp(data->str + index,
        ((char **) data->settings.separator)[i],
        my_strlen(((char **) data->settings.separator)[i])) == 0) {
            data->last_separator_size =
                my_strlen(((char **) data->settings.separator)[i]);
            return true;
        }
    }
    return false;
}

static bool update_inhibitor(str_to_array_t *data,
    char current_char)
{
    if (my_char_is(data->inhibitor, data->settings.inhibitors_single) == true
    || data->inhibitor == current_char) {
        data->inhibitor = '\0';
        return true;
    }
    if (data->inhibitor == '\0' &&
    (my_char_is(current_char, data->settings.inhibitors_single) == true
    || my_char_is(current_char, data->settings.inhibitors_double) == true)) {
        data->inhibitor = current_char;
        return true;
    }
    return false;
}

static void calculate_number_of_words(str_to_array_t *data)
{
    bool can_add_word = true;

    for (size_t index = 0; data->str[index] != '\0'; index++) {
        if (is_separator[data->settings.type](data, index) == false
        && can_add_word == true) {
            data->nb_words++;
            can_add_word = false;
        }
        if (update_inhibitor(data, data->str[index]) == true)
            continue;
        if (data->inhibitor == '\0' && is_separator[data->settings.type]
        (data, index) == true) {
            can_add_word = true;
            index += data->last_separator_size -1;
        }
    }
}

static void move_to_next_word(str_to_array_t *data)
{
    for (; data->str[data->saved_index] != '\0'
    && (is_separator[data->settings.type](data, data->saved_index) == true
    || is_inhibitor(data, data->saved_index) == true);
    data->saved_index++) {
        data->saved_index += data->last_separator_size - 1;
        if (is_inhibitor(data, data->saved_index))
            break;
    }
    data->nb_letters = 0;
    data->inhibitor = '\0';
}

static void count_next_word_letters(str_to_array_t *data)
{
    for (; data->str[data->saved_index] != '\0' && (!is_separator
    [data->settings.type](data, data->saved_index) || data->inhibitor != '\0'
    || is_inhibitor(data, data->saved_index)); data->saved_index++) {
        if (data->inhibitor == '\0' &&
        is_inhibitor(data, data->saved_index)) {
            data->inhibitor = data->str[data->saved_index];
            continue;
        }
        if (data->str[data->saved_index] == data->inhibitor && my_char_is(
        data->str[data->saved_index], data->settings.inhibitors_double)) {
            data->inhibitor = '\0';
            continue;
        }
        if (my_char_is(data->inhibitor,
        data->settings.inhibitors_single) == true)
            data->inhibitor = '\0';
        AL(FALSE, my_push_back, &data->next_word,
            (void *) &data->str[data->saved_index], UNKNOWN);
        data->nb_letters++;
    }
}

static char *get_next_word(str_to_array_t *data)
{
    char *next_word = my_calloc(data->nb_letters + 1, sizeof(char));
    size_t index = 0;

    for (node_t *tmp = data->next_word; tmp != NULL; tmp = tmp->next) {
        if (tmp->data != NULL) {
            next_word[index] = ((char *) tmp->data)[0];
            index++;
        }
    }
    my_delete_list(&data->next_word);
    return next_word;
}

/**
 * @brief Returns an array of words delimited
 * by a separator (array_settings.separator) from a string (str)
 * @note Compared to my_str_to_word_array,
 * this function will use an array_settings to personalize the conversion
 * @param str The string to convert
 * @param array_settings The settings for the convertion
 * @return <b>char**</b> The array of words
 * @author Nicolas TORO
 */
char **my_str_to_array(const char *str, array_settings_t array_settings)
{
    str_to_array_t data = {str, array_settings, 0, 1, '\0', 0, 0, NULL, NULL};

    if (str == NULL)
        return NULL;
    calculate_number_of_words(&data);
    if (data.nb_words == 0)
        return NULL;
    data.array = my_calloc(data.nb_words + 1, sizeof(char *));
    for (size_t word_index = 0; word_index < data.nb_words; word_index++) {
        move_to_next_word(&data);
        count_next_word_letters(&data);
        data.array[word_index] = get_next_word(&data);
    }
    return data.array;
}

const is_separator_t is_separator[] = {
    &is_default_separator,
    &is_char_separator,
    &is_string_separator
};
