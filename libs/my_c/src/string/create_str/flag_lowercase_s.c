/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** Flag to print a %s (a string)
*/
/**
 * @file flag_lowercase_s.c
 * @brief The file containing the flag_lowercase_s function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static char *get_text(format_t *str_struct)
{
    char *result = NULL;
    wchar_t *tmp = NULL;
    size_t len = 0;

    if (str_struct->current_flag.specifier_id <= 2) {
        result = va_arg(str_struct->format_list, char *);
        len = (str_struct->current_flag.precision) ?
            str_struct->current_flag.precision_value : my_strlen(result);
        result = my_strndup(result, len);
    } else {
        tmp = va_arg(str_struct->format_list, wchar_t *);
        len = (str_struct->current_flag.precision) ?
            str_struct->current_flag.precision_value : my_wcslen(tmp);
        result = my_calloc(len + 1, sizeof(char));
        if (my_wcstombs(result, tmp, len) == -1) {
            str_struct->invalid_status = true;
            return FREE(result);
        }
    }
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

void flag_lowercase_s(format_t *str_struct)
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
        for (ssize_t i = 0; i < str_struct->current_flag.width; i++)
            str_list[1][i] = ' ';
    }
    add_text(str_struct, str_list);
}
