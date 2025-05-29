/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_putstr_error function
*/
/**
 * @file my_putstr_error.c
 * @brief The file containing the my_putstr_error function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Prints a string (str) in stderr and returns 84
 * @param str The string to print
 * @return <b>int</b> <u>84</u>
 * @author Nicolas TORO
 */
int my_putstr_error(char const *str)
{
    if (str == NULL)
        return FAILURE;
    write(2, str, my_strlen(str));
    return FAILURE;
}
