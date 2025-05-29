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
 * @return <b>int</b> <u>1</u> if the string is alphabetical,
 * <u>0</u> otherwise
 * @author Nicolas TORO
 */
int my_str_is_alpha(char const *str)
{
    for (int i = 0; i < my_strlen(str); i++) {
        if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i] > 'z')
            return 0;
    }
    return 1;
}
