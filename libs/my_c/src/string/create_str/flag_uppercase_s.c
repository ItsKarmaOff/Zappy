/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_uppercase_s function
*/
/**
 * @file flag_uppercase_s.c
 * @brief The file containing the flag_uppercase_s function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static char *get_text(format_t *str_struct)
{
    char **array = va_arg(str_struct->format_list, char **);
    intmax_t array_len = my_array_len((void **)array);
    intmax_t total_len = my_word_array_len(array, array_len);
    char *tmp = my_calloc((array_len -1) * 4 + total_len + 5, sizeof(char));
    char *result = NULL;

    my_strcat(tmp, "[\"");
    for (int index = 0; index < array_len; index++) {
        my_strcat(tmp, array[index]);
        if (index != array_len - 1)
            my_strcat(tmp, "\", \"");
    }
    my_strcat(tmp, "\"]");
    if (str_struct->current_flag.precision) {
        result = my_strndup(tmp, str_struct->current_flag.precision_value);
        FREE(tmp);
    } else
        result = tmp;
    return result;
}

static void add_text(format_t *str_struct, char **str_list)
{
    if (!str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[1], STRING);
    my_push_back(&str_struct->str_list, str_list[0], STRING);
    if (str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[1], STRING);
}

void flag_uppercase_s(format_t *str_struct)
{
    char *str_list[] = {NULL, NULL};

    str_list[0] = get_text(str_struct);
    str_struct->total_len += my_strlen(str_list[0]);
    str_struct->current_flag.width -= my_strlen(str_list[0]);
    if (str_struct->current_flag.width <= 0)
        str_list[1] = NULL;
    else {
        str_struct->total_len += str_struct->current_flag.width;
        str_list[1] = my_calloc(str_struct->current_flag.width
                                + 1, sizeof(char));
        for (int i = 0; i < str_struct->current_flag.width; i++)
            str_list[1][i] = ' ';
    }
    add_text(str_struct, str_list);
}
