/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_char_is_alpha function
*/
/**
 * @file my_char_is_alpha.c
 * @brief The file containing the my_char_is_alpha function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a char (c) is a letter
 * @param c The char to check
 * @return <b>bool</b> <u>1</u> if the char is a letter, <u>0</u> otherwise
 * @author Nicolas TORO
 */
bool my_char_is_alpha(char c)
{
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return true;
    return false;
}
