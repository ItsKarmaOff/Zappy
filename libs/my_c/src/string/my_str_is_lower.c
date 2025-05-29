/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_str_is_lower function
*/
/**
 * @file my_str_islower.c
 * @brief The file containing the my_str_is_lower function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a string (str) is lowercase
 * @param str The string to check
 * @return <b>int</b> <u>1</u> if the string is lowercase, <u>0</u> otherwise
 * @author Nicolas TORO
 */
int my_str_is_lower(char const *str)
{
    if (my_str_is_alpha(str) == 0)
        return 0;
    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] < 'a' || str[i] > 'z')
            return 0;
    }
    return 1;
}
