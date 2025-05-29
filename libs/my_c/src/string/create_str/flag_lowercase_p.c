/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_lowercase_p function
*/
/**
 * @file flag_lowercase_p.c
 * @brief The file containing the flag_lowercase_p function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static void add_text(format_t *str_struct, char **str_list)
{
    if (!str_struct->current_flag.attributes[0]
        && !str_struct->current_flag.attributes[4])
        my_push_back(&str_struct->str_list, str_list[3], STRING);
    my_push_back(&str_struct->str_list, str_list[0], STRING);
    if (!str_struct->current_flag.attributes[0]
        && str_struct->current_flag.attributes[4])
        my_push_back(&str_struct->str_list, str_list[3], STRING);
    my_push_back(&str_struct->str_list, str_list[1], STRING);
    my_push_back(&str_struct->str_list, str_list[2], STRING);
    if (str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[3], STRING);
}

void flag_lowercase_p(format_t *str_struct)
{
    char *str_list[] = {NULL, NULL, NULL, NULL};
    void *nbr = va_arg(str_struct->format_list, void *);

    str_list[0] = my_strdup("0x");
    str_list[2] = my_nbr_to_str_unsigned(
        (uintmax_t)nbr, BASE_16_LOWERCASE, sizeof(void *));
    str_list[1] = get_precision(str_struct, str_list[1]);
    str_list[3] = get_width(str_struct, str_list, 3);
    add_text(str_struct, str_list);
}
