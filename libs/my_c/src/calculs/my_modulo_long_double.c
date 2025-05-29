/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The my_modulo_long_double.c
*/
/**
 * @file my_modulo_long_double.c
 * @brief The my_modulo_long_double.c
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the modulo of two long double
 * @param x The first long double
 * @param y The second long double
 * @return <b>float</b> The modulo of the two long double
 * @author Nicolas TORO
 */
long double my_modulo_long_double(long double x, long double y)
{
    if (y == 0.0f || my_isnan_long_double(x) || my_isnan_long_double(y)
    || my_isinf_long_double(x))
        return 0.0 / 0.0;
    if (x == 0.0f || my_isinf_long_double(y))
        return x;
    return x - (ceil(x / y) * y);
}
