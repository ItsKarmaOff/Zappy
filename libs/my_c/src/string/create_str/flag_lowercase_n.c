/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_lowercase_n function
*/
/**
 * @file flag_lowercase_n.c
 * @brief The file containing the flag_lowercase_n function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static void len_to_char(format_t *str_struct)
{
    char *var = va_arg(str_struct->format_list, char *);

    *var = str_struct->total_len;
}

static void len_to_short(format_t *str_struct)
{
    short *var = va_arg(str_struct->format_list, short *);

    *var = str_struct->total_len;
}

static void len_to_int(format_t *str_struct)
{
    int *var = va_arg(str_struct->format_list, int *);

    *var = str_struct->total_len;
}

static void len_to_long(format_t *str_struct)
{
    long *var = va_arg(str_struct->format_list, long *);

    *var = str_struct->total_len;
}

static void len_to_long_long(format_t *str_struct)
{
    long long *var = va_arg(str_struct->format_list, long long *);

    *var = str_struct->total_len;
}

static void len_to_intmax(format_t *str_struct)
{
    intmax_t *var = va_arg(str_struct->format_list, intmax_t *);

    *var = str_struct->total_len;
}

static void len_to_size(format_t *str_struct)
{
    size_t *var = va_arg(str_struct->format_list, size_t *);

    *var = str_struct->total_len;
}

static void len_to_ptrdiff(format_t *str_struct)
{
    ptrdiff_t *var = va_arg(str_struct->format_list, ptrdiff_t *);

    *var = str_struct->total_len;
}

void flag_lowercase_n(format_t *str_struct)
{
    void (*len_to_var[])(format_t *str_struct) = {&len_to_int,
        &len_to_char, &len_to_short, &len_to_long_long,
        &len_to_long, &len_to_intmax, &len_to_intmax,
        &len_to_ptrdiff, &len_to_long_long};

    len_to_var[str_struct->current_flag.specifier_id](str_struct);
}
