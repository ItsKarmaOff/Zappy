/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_char_is function
*/
/**
 * @file my_char_is.c
 * @brief The file containing the my_char_is function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Checks if a char (c) is in a list of chars (char_list)
 * @param c The char to check
 * @param char_list The list of chars to check
 * @return <b>int</b> <u>1</u> if the char is in the list, <u>0</u> otherwise
 * @author Nicolas TORO
 */
int my_char_is(char c, const char *char_list)
{
    for (int i = 0; char_list[i]; i++)
        if (c == char_list[i])
            return 1;
    return 0;
}
