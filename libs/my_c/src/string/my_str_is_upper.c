/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_str_is_upper function
*/
/**
 * @file my_str_isupper.c
 * @brief The file containing the my_str_is_upper function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a string (str) is uppercase
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is uppercase,
 * <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is_upper(char const *str)
{
    if (my_str_is_alpha(str) == 0)
        return false;
    for (size_t i = 0; i < my_strlen(str); i++) {
        if (str[i] < 'A' || str[i] > 'Z')
            return false;
    }
    return true;
}
