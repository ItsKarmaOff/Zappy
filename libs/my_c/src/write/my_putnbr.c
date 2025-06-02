/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_putnbr function
*/
/**
 * @file my_putnbr.c
 * @brief The file containing the my_putnbr function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void put_str_nb(intmax_t nb, size_t len_nb)
{
    char nb_str[len_nb];
    intmax_t figure_temp = nb;

    for (size_t i = 0; i < len_nb; i++) {
        nb_str[len_nb - i - 1] = 48 + (figure_temp % 10);
        figure_temp = (figure_temp - (figure_temp % 10)) / 10;
    }
    nb_str[len_nb] = '\0';
    my_putstr(nb_str);
}

/**
 * @brief Prints a number (nb) in stdout
 * @param nb The number to print
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_putnbr(intmax_t nb)
{
    size_t len_nb = 1;
    intmax_t temp_nb = nb;

    if (nb < 0) {
        my_putchar('-');
        nb = - nb;
    }
    while ((temp_nb / 10) != 0) {
        len_nb = len_nb + 1;
        temp_nb = temp_nb / 10;
    }
    put_str_nb(nb, len_nb);
}
