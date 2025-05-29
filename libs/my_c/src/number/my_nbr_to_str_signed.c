/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_nbr_to_str_signed function
*/
/**
 * @file my_nbr_to_str_signed.c
 * @brief The file containing the my_nbr_to_str_signed function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static char *nbr_to_str(int64_t nb, int len_nb,
    char const *base, int base_len)
{
    char *nb_str = my_calloc(len_nb + 2, sizeof(char));
    int64_t figure_temp = (nb < 0) ? - nb : nb;

    for (int i = 0; i < len_nb; i++) {
        nb_str[len_nb - i - (nb > 0)] = base[figure_temp % base_len];
        figure_temp = figure_temp / base_len;
    }
    if (nb < 0)
        nb_str[0] = '-';
    nb_str[len_nb + 1] = '\0';
    return nb_str;
}

/**
 * @brief Converts a number to a string
 * @param nbr The number to convert
 * @param base The base to convert the number
 * @return <b>char *</b> The number converted to a string
 * @author Nicolas TORO
 */
char *my_nbr_to_str_signed(int64_t nbr, char const *base)
{
    int64_t converted_nbr = nbr;
    int len_nb = 1;
    int64_t tmp_nb = ABS(converted_nbr);
    int base_len = my_strlen(base);

    if (base_len < 2)
        return NULL;
    if (nbr == 0)
        return my_strdup("0");
    while ((tmp_nb / base_len) != 0) {
        len_nb++;
        tmp_nb = tmp_nb / base_len;
    }
    return nbr_to_str(converted_nbr, len_nb, base, base_len);
}
