/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_char_is_printable function
*/
/**
 * @file my_char_is_printable.c
 * @brief The file containing the my_char_is_printable function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a char (c) is printable
 * @param c The char to check
 * @return <b>bool</b> <u>1</u> if the char is printable, <u>0</u> otherwise
 * @author Nicolas TORO
 */
bool my_char_is_printable(char const c)
{
    if (c >= 32 && c <= 126)
            return true;
    return false;
}
