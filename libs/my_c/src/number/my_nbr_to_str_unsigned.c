/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_nbr_to_str_unsigned function
*/
/**
 * @file my_nbr_to_str_unsigned.c
 * @brief The file containing the my_nbr_to_str_unsigned function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static char *nbr_to_str(size_t nb, size_t len_nb,
    char const *base, size_t base_len)
{
    char *nb_str = my_calloc(len_nb + 1, sizeof(char));
    size_t figure_temp = nb;

    for (size_t i = 0; i < len_nb; i++) {
        nb_str[len_nb - i - 1] = base[figure_temp % base_len];
        figure_temp = figure_temp / base_len;
    }
    nb_str[len_nb] = '\0';
    return nb_str;
}

/**
 * @brief Converts a number to a string
 * @param nbr The number to convert
 * @param base The base to convert the number
 * @param type_size The size of the type of the number
 * @return <b>char *</b> The number converted to a string
 * @author Nicolas TORO
 */
char *my_nbr_to_str_unsigned(uint64_t nbr, char const *base,
    uint64_t type_size)
{
    uint64_t converted_nbr = 0;
    int len_nb = 1;
    uint64_t tmp_nb;
    size_t base_len = my_strlen(base);

    if (base_len < 2)
        return NULL;
    if (nbr == 0)
        return my_strdup("0");
    my_memcpy(&converted_nbr, &nbr, type_size);
    tmp_nb = converted_nbr;
    while ((tmp_nb / base_len) != 0) {
        len_nb++;
        tmp_nb = tmp_nb / base_len;
    }
    return nbr_to_str(converted_nbr, len_nb, base, base_len);
}
