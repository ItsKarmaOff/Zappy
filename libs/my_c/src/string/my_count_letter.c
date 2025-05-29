/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_count_letter function
*/
/**
 * @file my_count_letter.c
 * @brief The file containing the my_count_letter function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Counts the number of times a letter (c) is in a string (str)
 * @param str The string to check
 * @param c The letter to count
 * @return <b>int</b> The number of times the letter is in the string
 * @author Nicolas TORO
 */
int my_count_letter(char const *str, char c)
{
    int count = 0;

    for (int index = 0; str[index] != '\0'; index++) {
        if (str[index] == c)
            count++;
    }
    return count;
}
