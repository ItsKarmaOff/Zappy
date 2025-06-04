/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_str_is function
*/
/**
 * @file my_str_is.c
 * @brief The file containing the my_str_is function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a string (str) is composed of characters
 * in the characters list (char_list) or 0 if not
 * @param str The string to check
 * @return <b>bool</b> <u>true</u> if the string is composed of characters
 * in the characters list (char_list), <u>false</u> otherwise
 * @author Nicolas TORO
 */
bool my_str_is(char *str, const char *char_list)
{
    for (size_t i = 0; str[i]; i++)
        if (!my_char_is(str[i], char_list))
            return false;
    return true;
}
