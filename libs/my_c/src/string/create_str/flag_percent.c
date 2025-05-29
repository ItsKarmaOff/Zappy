/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_percent function
*/
/**
 * @file flag_percent.c
 * @brief The file containing the flag_percent function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

void flag_percent(format_t *str_struct)
{
    my_push_back(&str_struct->str_list, my_strdup("%"), STRING);
    str_struct->total_len += 1;
}
