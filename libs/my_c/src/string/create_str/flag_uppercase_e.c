/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_uppercase_e function
*/
/**
 * @file flag_uppercase_e.c
 * @brief The file containing the flag_uppercase_e function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static char *str_from_double(format_t *str_struct)
{
    return NULL;
}

static char *str_from_long_double(format_t *str_struct)
{
    return NULL;
}

static void add_text(format_t *str_struct, char **str_list)
{
    if (!str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[2], STRING);
    my_push_back(&str_struct->str_list, str_list[0], STRING);
    my_push_back(&str_struct->str_list, str_list[1], STRING);
    if (str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[2], STRING);
}

void flag_uppercase_e(format_t *str_struct)
{
    char *(*nbr_to_str[])(format_t *str_struct) = {&str_from_double,
        &str_from_double, &str_from_double, &str_from_long_double,
        &str_from_double, &str_from_double, &str_from_double,
        &str_from_double, &str_from_long_double};
    char *str_list[] = {NULL, NULL, NULL};

    if (!str_struct->current_flag.precision)
        str_struct->current_flag.precision_value = 6;
    str_list[1] = nbr_to_str
    [str_struct->current_flag.specifier_id](str_struct);
    str_list[0] = str_struct->current_flag.sign;
    str_list[2] = get_width(str_struct, str_list, 3);
    add_text(str_struct, str_list);
}
