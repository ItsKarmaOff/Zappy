/*
** EPITECH PROJECT, 2024
** my_libs
** File description:
** The file containing the my_wcstombs function
*/
/**
 * @file my_wcstombs.c
 * @brief The file containing the my_wcstombs function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Converts a wide-character string to a multibyte string
 * @param dest The destination string
 * @param src The source string
 * @param n The number of bytes to convert
 * @return <b>intmax_t</b> The number of bytes converted if successful,
 * the length of the string if dest is NULL, -1 if an error occured
 */
intmax_t my_wcstombs(char *dest, const wchar_t *src, intmax_t n)
{
    intmax_t count = 0;

    if (src == NULL || n == 0)
        return 0;
    while (src[count] != L'\0') {
        if (src[count] > 127)
            return -1;
        count++;
    }
    if (dest == NULL)
        return count;
    for (intmax_t index = 0; src[index] != L'\0' && index < n; index++)
        dest[count] = (char)src[index];
    dest[count] = '\0';
    return n;
}
