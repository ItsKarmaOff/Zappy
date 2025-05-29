/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The attributes.c
*/
/**
 * @file attributes.c
 * @brief The attributes.c
 * @author Nicolas TORO
 */

#include "../../../include/my.h"

/**
 * @brief Update the sign attributes
 * @param format The format structure
 * @param nb The number to check
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void update_sign_attributes(format_t *str_struct, long double nb)
{
    if (nb < 0) {
        str_struct->current_flag.sign = my_strdup("-");
        return;
    }
    if (nb >= 0 && str_struct->current_flag.attributes[1]) {
        str_struct->current_flag.sign = my_strdup("+");
        return;
    }
    if (nb >= 0 && str_struct->current_flag.attributes[2]) {
        str_struct->current_flag.sign = my_strdup(" ");
        return;
    }
    str_struct->current_flag.sign = NULL;
}

/**
 * @brief Get the width string depending on attributes
 * @param str_struct The format structure
 * @param str_list The string list
 * @param len The length of the string list
 * @return <b>char*</b> The width string
 * @author Nicolas TORO
 */
char *get_width(format_t *str_struct, char **str_list, int len)
{
    char width_char = ' ';
    int str_size = my_word_array_len(str_list, len);
    char *width_str = NULL;

    str_struct->total_len += str_size;
    str_struct->current_flag.width -= my_word_array_len(str_list, len);
    if (str_struct->current_flag.width <= 0)
        return width_str;
    str_struct->total_len += str_struct->current_flag.width;
    if (str_struct->current_flag.attributes[4]
    && str_struct->current_flag.attributes[0] == false
    && (str_struct->current_flag.precision == false || my_char_is(
    FORMAT_FLAGS[str_struct->current_flag.flag_id - 1], "aAeEfFgG")))
        width_char = '0';
    width_str = my_calloc(str_struct->current_flag.width + 1, sizeof(char));
    for (int i = 0; i < str_struct->current_flag.width; i++)
        width_str[i] = width_char;
    return width_str;
}

/**
 * @brief Get the precision string
 * @param str_struct The format structure
 * @param nbr_str The number string
 * @return <b>char*</b> The precision string
 * @author Nicolas TORO
 */
char *get_precision(format_t *str_struct, char *nbr_str)
{
    char *precision_str = NULL;

    if (str_struct->current_flag.precision == false)
        return precision_str;
    str_struct->current_flag.precision_value -= my_strlen(nbr_str);
    if (str_struct->current_flag.precision_value <= 0)
        return precision_str;
    precision_str = my_calloc(str_struct->
        current_flag.precision_value + 1, sizeof(char));
    for (int i = 0; i < str_struct->current_flag.precision_value; i++)
        precision_str[i] = '0';
    return precision_str;
}
