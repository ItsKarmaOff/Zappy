/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_getnbr_base function
*/
/**
 * @file my_getnbr_base.c
 * @brief The file containing the my_getnbr_base function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static bool is_valid(char c, char const *base)
{
    for (size_t i = 0; i < my_strlen(base); i++) {
        if (c == base[i])
            return true;
    }
    if (c == '-' || c == '+')
        return true;
    return false;
}

static ssize_t calculate_base(char const *str, char const *base,
    size_t *index, int **ptr)
{
    if (is_valid(str[index[0]], base) == true) {
        if (str[index[0]] == '-') {
            *(ptr[0]) = - *(ptr[0]);
            return 0;
        }
        if (str[index[0]] == base[index[1]]) {
            return index[1] * my_compute_power(my_strlen(base),
            my_strlen(str) - index[0] - 1);
        }
    } else {
        *(ptr[1]) = 1;
    }
    return 0;
}

/**
 * @brief Returns a number starting from a string number (str)
 * in the requested base (base)
 * @note Returns 0 if the string is not a number
 * @note The function accept multiple signes in the string
 * @param str The string to convert
 * @param base The base of the number
 * @return <b>intmax_t</b> The number found in the string
 * @author Nicolas TORO
 */
intmax_t my_getnbr_base(char const *str, char const *base)
{
    intmax_t result = 0;
    int signe_save = 0;
    int signe = 1;
    int error = 0;
    size_t index[2];
    int *ptr[2];

    for (ssize_t i = my_strlen(str) - 1; i >= 0; i--) {
        for (size_t j = 0; j < my_strlen(base)
        && error == 0 && signe == 1; j++) {
            index[0] = i;
            index[1] = j;
            ptr[0] = &signe;
            ptr[1] = &error;
            result = result + calculate_base(str, base, index, ptr);
        }
        signe_save = signe;
        signe = 1;
    }
    return result * signe_save;
}
