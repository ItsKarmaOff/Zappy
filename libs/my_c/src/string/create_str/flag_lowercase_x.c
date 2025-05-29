/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the flag_lowercase_x function
*/
/**
 * @file flag_lowercase_x.c
 * @brief The file containing the flag_lowercase_x function
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

static char *str_from_char(format_t *str_struct)
{
    unsigned char nbr = va_arg(
    str_struct->format_list, unsigned int);
    char *converted_nbr = my_nbr_to_str_unsigned(
        nbr, BASE_16_LOWERCASE, sizeof(unsigned char));

    return converted_nbr;
}

static char *str_from_short(format_t *str_struct)
{
    unsigned short nbr = va_arg(
    str_struct->format_list, unsigned int);
    char *converted_nbr = my_nbr_to_str_unsigned(
        nbr, BASE_16_LOWERCASE, sizeof(unsigned short));

    return converted_nbr;
}

static char *str_from_uint(format_t *str_struct)
{
    unsigned int nbr = va_arg(
    str_struct->format_list, unsigned int);
    char *converted_nbr = my_nbr_to_str_unsigned(
        nbr, BASE_16_LOWERCASE, sizeof(unsigned int));

    return converted_nbr;
}

static char *str_from_long(format_t *str_struct)
{
    unsigned long nbr = va_arg(
    str_struct->format_list, unsigned long);
    char *converted_nbr = my_nbr_to_str_unsigned(
        nbr, BASE_16_LOWERCASE, sizeof(unsigned long));

    return converted_nbr;
}

static char *str_from_long_long(format_t *str_struct)
{
    unsigned long long nbr = va_arg(
    str_struct->format_list, unsigned long long);
    char *converted_nbr = my_nbr_to_str_unsigned(
        nbr, BASE_16_LOWERCASE, sizeof(unsigned long long));

    return converted_nbr;
}

static char *str_from_uintmax(format_t *str_struct)
{
    uintmax_t nbr = va_arg(str_struct->format_list, uintmax_t);
    char *converted_nbr = my_nbr_to_str_unsigned(
        nbr, BASE_16_LOWERCASE, sizeof(uintmax_t));

    return converted_nbr;
}

static char *str_from_size(format_t *str_struct)
{
    size_t nbr = va_arg(str_struct->format_list, size_t);
    char *converted_nbr = my_nbr_to_str_unsigned(
        nbr, BASE_16_LOWERCASE, sizeof(size_t));

    return converted_nbr;
}

static char *str_from_ptrdiff(format_t *str_struct)
{
    ptrdiff_t nbr = va_arg(str_struct->format_list, ptrdiff_t);
    char *converted_nbr = my_nbr_to_str_unsigned(
        nbr, BASE_16_LOWERCASE, sizeof(ptrdiff_t));

    return converted_nbr;
}

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

void flag_lowercase_x(format_t *str_struct)
{
    char *(*nbr_to_str[])(format_t *str_struct) = {&str_from_uint,
        &str_from_char, &str_from_short, &str_from_long_long,
        &str_from_long, &str_from_uintmax, &str_from_size,
        &str_from_ptrdiff, &str_from_long_long};
    char *str_list[] = {NULL, NULL, NULL, NULL};

    str_list[0] = (str_struct->current_flag.attributes[3]) ?
        my_strdup("0x") : NULL;
    str_list[2] = nbr_to_str
        [str_struct->current_flag.specifier_id](str_struct);
    str_list[1] = get_precision(str_struct, str_list[1]);
    str_list[3] = get_width(str_struct, str_list, 3);
    add_text(str_struct, str_list);
}
