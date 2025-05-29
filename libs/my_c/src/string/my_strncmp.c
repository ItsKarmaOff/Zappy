/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strncmp function
*/
/**
 * @file my_strncmp.c
 * @brief The file containing the my_strncmp function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Compares two strings (s1) and (s2) with a defined size (n)
 * @param s1 The first string to compare
 * @param s2 The second string to compare
 * @param n The size of the strings to compare
 * @return <b>int</b> <u>0</u> if the strings are identical, otherwise
 * the difference between the first different characters in the strings
 * @author Nicolas TORO
 */
int my_strncmp(char const *s1, char const *s2, int n)
{
    int i = 0;

    if (s1 == NULL && s2 == NULL)
        return 0;
    if (s1 == NULL)
        return 0 - s2[0];
    if (s2 == NULL)
        return s1[0] - 0;
    while (s1[i] != '\0' && s2[i] != '\0' && i + 1 < n) {
        if (s1[i] < s2[i])
            return s1[i] - s2[i];
        if (s1[i] > s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}
