/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_str_is_alpha function
*/
/**
 * @file my_str_is_alpha.c
 * @brief The file containing the my_str_is_alpha function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a string (str) is alphabetical
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is alphabetical,
 * <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is_alpha(char const *str)
{
    for (size_t i = 0; i < my_strlen(str); i++) {
        if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
            return false;
    }
    return true;
}
