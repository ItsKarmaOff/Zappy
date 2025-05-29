/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_str_is_printable function
*/
/**
 * @file my_str_is_printable.c
 * @brief The file containing the my_str_is_printable function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a string (str) is printable
 * @param str The string to check
 * @return <b>int</b> <u>1</u> if the string is printable, <u>0</u> otherwise
 * @author Nicolas TORO
 */
int my_str_is_printable(char const *str)
{
    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] < 32 || str[i] == 127)
            return 0;
    }
    return 1;
}
