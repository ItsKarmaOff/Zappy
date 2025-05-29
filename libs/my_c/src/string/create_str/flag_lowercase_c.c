/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_lowercase_c function
*/
/**
 * @file flag_lowercase_c.c
 * @brief The file containing the flag_lowercase_c function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static char *get_text(format_t *str_struct)
{
    char *result = NULL;
    char tmp_c = 0;
    wchar_t tmp_wc = 0;

    if (str_struct->current_flag.specifier_id <= 2) {
        tmp_c = va_arg(str_struct->format_list, int);
        result = my_strndup(&tmp_c, 1);
    } else {
        tmp_wc = va_arg(str_struct->format_list, wchar_t);
        result = my_calloc(2, sizeof(char));
        if (my_wcstombs(result, &tmp_wc, 1) == -1) {
            str_struct->status = -1;
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

void flag_lowercase_c(format_t *str_struct)
{
    char *str_list[] = {NULL, NULL, NULL};

    str_list[0] = get_text(str_struct);
    str_struct->total_len += 1;
    str_struct->current_flag.width -= 1;
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
