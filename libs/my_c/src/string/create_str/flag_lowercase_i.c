/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_lowercase_i function
*/
/**
 * @file flag_lowercase__i.c
 * @brief The file containing the flag_lowercase_i function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static char *str_from_char(format_t *str_struct)
{
    signed char nbr = va_arg(str_struct->format_list, int);
    char *converted_nbr = my_nbr_to_str_signed(nbr, BASE_10);
    char *result_str = NULL;

    update_sign_attributes(str_struct, nbr);
    if (nbr < 0)
        result_str = my_strdup(converted_nbr + 1);
    else
        result_str = my_strdup(converted_nbr);
    free(converted_nbr);
    return result_str;
}

static char *str_from_short(format_t *str_struct)
{
    short nbr = va_arg(str_struct->format_list, int);
    char *converted_nbr = my_nbr_to_str_signed(nbr, BASE_10);
    char *result_str = NULL;

    update_sign_attributes(str_struct, nbr);
    if (nbr < 0)
        result_str = my_strdup(converted_nbr + 1);
    else
        result_str = my_strdup(converted_nbr);
    free(converted_nbr);
    return result_str;
}

static char *str_from_int(format_t *str_struct)
{
    int nbr = va_arg(str_struct->format_list, int);
    char *converted_nbr = my_nbr_to_str_signed(nbr, BASE_10);
    char *result_str = NULL;

    update_sign_attributes(str_struct, nbr);
    if (nbr < 0)
        result_str = my_strdup(converted_nbr + 1);
    else
        result_str = my_strdup(converted_nbr);
    free(converted_nbr);
    return result_str;
}

static char *str_from_long(format_t *str_struct)
{
    long nbr = va_arg(str_struct->format_list, long);
    char *converted_nbr = my_nbr_to_str_signed(nbr, BASE_10);
    char *result_str = NULL;

    update_sign_attributes(str_struct, nbr);
    if (nbr < 0)
        result_str = my_strdup(converted_nbr + 1);
    else
        result_str = my_strdup(converted_nbr);
    free(converted_nbr);
    return result_str;
}

static char *str_from_long_long(format_t *str_struct)
{
    long long nbr = va_arg(str_struct->format_list, long long);
    char *converted_nbr = my_nbr_to_str_signed(nbr, BASE_10);
    char *result_str = NULL;

    update_sign_attributes(str_struct, nbr);
    if (nbr < 0)
        result_str = my_strdup(converted_nbr + 1);
    else
        result_str = my_strdup(converted_nbr);
    free(converted_nbr);
    return result_str;
}

static char *str_from_intmax(format_t *str_struct)
{
    intmax_t nbr = va_arg(str_struct->format_list, intmax_t);
    char *converted_nbr = my_nbr_to_str_signed(nbr, BASE_10);
    char *result_str = NULL;

    update_sign_attributes(str_struct, nbr);
    if (nbr < 0)
        result_str = my_strdup(converted_nbr + 1);
    else
        result_str = my_strdup(converted_nbr);
    free(converted_nbr);
    return result_str;
}

static char *str_from_ptrdiff(format_t *str_struct)
{
    ptrdiff_t nbr = va_arg(str_struct->format_list, ptrdiff_t);
    char *converted_nbr = my_nbr_to_str_signed(nbr, BASE_10);
    char *result_str = NULL;

    update_sign_attributes(str_struct, nbr);
    if (nbr < 0)
        result_str = my_strdup(converted_nbr + 1);
    else
        result_str = my_strdup(converted_nbr);
    free(converted_nbr);
    return result_str;
}

static void add_text(format_t *str_struct, char **str_list)
{
    if (!str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[3], STRING);
    my_push_back(&str_struct->str_list, str_list[0], STRING);
    my_push_back(&str_struct->str_list, str_list[1], STRING);
    my_push_back(&str_struct->str_list, str_list[2], STRING);
    if (str_struct->current_flag.attributes[0])
        my_push_back(&str_struct->str_list, str_list[3], STRING);
}

void flag_lowercase_i(format_t *str_struct)
{
    char *(*nbr_to_str[])(format_t *str_struct) = {&str_from_int,
        &str_from_char, &str_from_short, &str_from_long_long,
        &str_from_long, &str_from_intmax, &str_from_intmax,
        &str_from_ptrdiff, &str_from_long_long};
    char *str_list[] = {NULL, NULL, NULL, NULL};

    str_list[2] = nbr_to_str
    [str_struct->current_flag.specifier_id](str_struct);
    str_list[0] = str_struct->current_flag.sign;
    str_list[1] = get_precision(str_struct, str_list[2]);
    str_list[3] = get_width(str_struct, str_list, 3);
    add_text(str_struct, str_list);
}
