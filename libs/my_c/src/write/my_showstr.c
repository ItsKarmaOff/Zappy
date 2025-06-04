/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_showstr function
*/
/**
 * @file my_showstr.c
 * @brief The file containing the my_showstr function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void check_zero_in_hexadecimal(char c)
{
    if (c < 16)
        my_putchar('0');
}

/**
 * @brief Prints a string (str) but replaces
 * non-printable characters with their hexadecimal number
 * @param str The string to print
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_showstr(char const *str)
{
    size_t len = my_strlen(str);

    for (size_t i = 0; i < len; i++) {
        if (my_char_is_printable(str[i]) == 1) {
            my_putchar(str[i]);
        } else {
            my_putchar('\\');
            check_zero_in_hexadecimal(str[i]);
            my_putnbr_base(str[i], "0123456789abcedf");
        }
    }
}
