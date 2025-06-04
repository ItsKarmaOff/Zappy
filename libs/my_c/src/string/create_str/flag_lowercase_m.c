/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_lowercase_m function
*/
/**
 * @file flag_m.c
 * @brief The file containing the flag_lowercase_m function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static char *get_text(format_t *str_struct)
{
    char *result = NULL;

    if (str_struct->current_flag.precision)
        result = my_strndup(my_strerror(errno),
            str_struct->current_flag.precision_value);
    else
        result = my_strdup(my_strerror(errno));
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

void flag_lowercase_m(format_t *str_struct)
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
