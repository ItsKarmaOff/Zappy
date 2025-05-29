/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_nbr_long_double_to_str function
*/
/**
 * @file my_nbr_long_double_to_str.c
 * @brief The file containing the my_nbr_long_double_to_str function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static intmax_t get_nbr_len(long double nbr, intmax_t precision,
    bool decimal_point)
{
    intmax_t len_nb = 1;
    long double tmp_nb = ABS(nbr);

    while ((tmp_nb / 10.0L) > 0.0L) {
        len_nb++;
        tmp_nb = tmp_nb / 10.0L;
    }
    if (nbr < 0.0L)
        len_nb++;
    if (decimal_point || precision > 0)
        len_nb += 1;
    return len_nb;
}

static void add_integer_part(char *nb_str, long double integer_part)
{
    if (integer_part < 0.0L)
        my_add_chr(nb_str, '-');
    integer_part = ABS(integer_part);
    while ((integer_part / 10.0L) > 0.0L) {
        my_add_chr(nb_str, fmodl(integer_part, 10.0L) + '0');
        integer_part = integer_part / 10.0L;
    }
    my_add_chr(nb_str, integer_part + '0');
    my_revstr(nb_str + ((nb_str[0] == '-') ? 1 : 0));
}

static void add_decimal_part(char *nb_str, long double decimal_part,
    bool decimal_point, intmax_t precision)
{
    long double integer_part = 0.0L;

    if (decimal_point || precision > 0)
        my_add_chr(nb_str, '.');
    for (intmax_t i = 0; i < precision; i++) {
        decimal_part *= 10.0L;
        my_split_long_double(decimal_part, &integer_part);
        my_add_chr(nb_str, integer_part + '0');
        decimal_part -= integer_part;
    }
}

static void round_long_double_string(char *nb_str, intmax_t precision)
{
    node_t *tmp = NULL;
    intmax_t len_nb = my_strlen(nb_str);
    char old_val = nb_str[len_nb - 1];
    bool round_status = true;

    for (intmax_t i = len_nb - 2; i >= 0; i--) {
        if (my_char_is_num(nb_str[i]) == false) {
            my_push_front(&tmp, my_strndup(nb_str + i, 1), STRING);
            continue;
        }
        if (round_status && old_val <= '5')
            round_status = false;
        old_val = nb_str[i] + round_status;
        my_push_front(&tmp, my_strndup(&old_val, 1), STRING);
    }
    my_memset(nb_str, 0, len_nb);
    for (node_t *node = tmp; node != NULL; node = node->next)
        my_add_chr(nb_str, *(char *)node->data);
    my_replace_char(nb_str, ':', '0');
    my_delete_list(&tmp);
}

static char *get_long_double_string(double nbr, intmax_t precision,
    bool decimal_point)
{
    long double integer_part = 0.0L;
    long double decimal_part = my_split_long_double(nbr, &integer_part);
    intmax_t len_nb = get_nbr_len(nbr, precision, decimal_point);
    char *nb_str = my_calloc(len_nb + precision + 2, sizeof(char));

    precision = precision + 1;
    add_integer_part(nb_str, integer_part);
    add_decimal_part(nb_str, decimal_part, decimal_point, precision);
    round_long_double_string(nb_str, precision);
    return nb_str;
}

/**
 * @brief Converts a number to a string
 * @param nbr The number to convert
 * @param precision The precision of the number
 * @param decimal_point The decimal point
 * @return <b>char *</b> The number converted to a string
 * @author Nicolas TORO
 */
char *my_nbr_long_double_to_str(long double nbr, intmax_t precision,
    bool decimal_point)
{
    if (my_isnan_long_double(nbr))
        return my_strdup("-nan");
    if (my_isinf_long_double(nbr) && nbr < 0.0L)
        return my_strdup("-inf");
    if (my_isinf_long_double(nbr) && nbr > 0.0L)
        return my_strdup("inf");
    return get_long_double_string(nbr, precision, decimal_point);
}
