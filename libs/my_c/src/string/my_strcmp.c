/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strcmp function
*/
/**
 * @file my_strcmp.c
 * @brief The file containing the my_strcmp function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Compares two strings (s1) and (s2)
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @return <b>int</b> <u>0</u> if the strings are identical, otherwise
 * the difference between the first different characters in the strings
 * @author Nicolas TORO
 */
int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    if (s1 == NULL && s2 == NULL)
        return 0;
    if (s1 == NULL)
        return 0 - s2[0];
    if (s2 == NULL)
        return s1[0] - 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] < s2[i])
            return -1;
        if (s1[i] > s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}
