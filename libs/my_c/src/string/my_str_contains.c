/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_sort_list function
*/
/**
 * @file my_str_contains.c
 * @brief The file containing the my_str_contains function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static int check_char_list(char *str, char *char_list, int i)
{
    for (int j = 0; char_list[j] != '\0'; j++) {
        if (str[i] == char_list[j])
            return 1;
    }
    return 0;
}

/**
 * @brief Checks if a string (str) contains a character
 * in a list of characters (char_list)
 * @param str The string to check
 * @param char_list The list of characters to check
 * @return <b>int</b> <u>1</u> if the string contains a character in the list,
 * <u>0</u> otherwise
 * @author Nicolas TORO
 */
int my_str_contains(char *str, char *char_list)
{
    if (str == NULL || char_list == NULL)
        return 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (check_char_list(str, char_list, i))
            return 1;
    }
    return 0;
}
