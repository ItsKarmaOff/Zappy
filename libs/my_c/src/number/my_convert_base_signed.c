/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_convert_base_signed function
*/
/**
 * @file my_convert_base_signed.c
 * @brief The file containing the my_convert_base_signed function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the result of the conversion of a number (nbr)
 * in a specific base (base_from) to another base (base_to)
 * @param nbr The number to convert
 * @param base_from The base of the number
 * @param base_to The base to convert the number
 * @return <b>char*</b> The converted number in the new base
 * @author Nicolas TORO
 */
char *my_convert_base_signed(char const *nbr,
    char const *base_from, char const *base_to)
{
    int64_t number = my_getnbr_base(nbr, base_from);

    return my_nbr_to_str_signed(number, base_to);
}
