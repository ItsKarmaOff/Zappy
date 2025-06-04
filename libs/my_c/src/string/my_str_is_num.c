/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_sort_list function
*/
/**
 * @file my_str_isnum.c
 * @brief The file containing the my_str_isnum function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a string (str) is a number
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is a number,
 * <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is_num(char const *str)
{
    for (size_t i = 0; i < my_strlen(str); i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}
