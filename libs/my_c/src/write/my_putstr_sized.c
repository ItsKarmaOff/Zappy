/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_putstr_sized function
*/
/**
 * @file my_putstr_sized.c
 * @brief The file containing the my_putstr_sized function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Prints a string (str) in stdout with a defined size (size)
 * and returns the length of the printed string
 * @param str The string to print
 * @param size The size of the string
 * @return <b>size_t</b> The length of the printed string
 * @author Nicolas TORO
 */
size_t my_putstr_sized(char const *str, size_t size)
{
    if (str == NULL || size < 1)
        return 0;
    write(1, str, size);
    return size;
}
