/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_putnbr_base function
*/
/**
 * @file my_putnbr_base.c
 * @brief The file containing the my_putnbr_base function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void put_str_nb(intmax_t nb, size_t len_nb,
    char const *base, size_t base_len)
{
    char nb_str[len_nb];
    intmax_t figure_temp = nb;

    for (size_t i = 0; i < len_nb; i++) {
        nb_str[len_nb - i - 1] = base[figure_temp % base_len];
        figure_temp = (figure_temp - (figure_temp % base_len)) / base_len;
    }
    nb_str[len_nb] = '\0';
    my_putstr(nb_str);
}

/**
 * @brief Prints a number (nb) in the requested base (base) in stdout
 * @param nbr The number to print
 * @param base The base to use
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_putnbr_base(intmax_t nbr, char const *base)
{
    size_t len_nb = 1;
    intmax_t temp_nb = nbr;
    size_t base_len = 0;

    if (nbr < 0) {
        my_putchar('-');
        nbr = - nbr;
    }
    while (base[base_len] != '\0')
        base_len = base_len + 1;
    while ((temp_nb / base_len) != 0) {
        len_nb = len_nb + 1;
        temp_nb = temp_nb / base_len;
    }
    put_str_nb(nbr, len_nb, base, base_len);
}
