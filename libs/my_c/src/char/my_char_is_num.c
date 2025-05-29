/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_char_is_num function
*/
/**
 * @file my_char_is_num.c
 * @brief The file containing the my_char_is_num function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a char (c) is a number
 * @param c The char to check
 * @return <b>int</b> <u>1</u> if the char is a number, <u>0</u> otherwise
 * @author Nicolas TORO
 */
int my_char_is_num(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    return 0;
}
