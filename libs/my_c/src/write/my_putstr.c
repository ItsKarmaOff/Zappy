/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_putstr function
*/
/**
 * @file my_putstr.c
 * @brief The file containing the my_putstr function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Writes a string (str) in stdout
 * and returns the length of the printed string
 * @param str The string to print
 * @return <b>size_t</b> The length of the printed string
 * @author Nicolas TORO
 */
size_t my_putstr(char const *str)
{
    size_t len;

    if (str == NULL)
        return 0;
    len = my_strlen(str);
    write(1, str, len);
    return len;
}
