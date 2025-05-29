/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_get_char_index function
*/
/**
 * @file my_get_char_index.c
 * @brief The file containing the my_get_char_index function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Get the index of a char in a str according to its occurrence
 * @param str The string to check
 * @param c The letter to find
 * @param occurrence The occurrence of the letter to find
 * @return <b>int</b> <u>-1</u> if the letter is not found, otherwise
 * the index of the letter in the string
 */
int my_get_char_index(char *str, char c, int occurrence)
{
    int index = -1;
    int count = 0;

    if (str == NULL)
        return index;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) {
            index = i;
            count++;
        }
        if (count == occurrence)
            break;
    }
    return index;
}
