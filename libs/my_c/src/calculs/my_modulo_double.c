/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The my_modulo_double.c
*/
/**
 * @file my_modulo_double.c
 * @brief The my_modulo_double.c
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the modulo of two double
 * @param x The first double
 * @param y The second double
 * @return <b>float</b> The modulo of the two double
 * @author Nicolas TORO
 */
double my_modulo_double(double x, double y)
{
    if (y == 0.0f || my_isnan_double(x) || my_isnan_double(y)
    || my_isinf_double(x))
        return 0.0 / 0.0;
    if (x == 0.0f || my_isinf_double(y))
        return x;
    return x - (ceil(x / y) * y);
}
