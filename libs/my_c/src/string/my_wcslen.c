/*
** EPITECH PROJECT, 2024
** my_libs
** File description:
** The file containing the my_wcslen function
*/
/**
 * @file my_wcslen.c
 * @brief The file containing the my_wcslen function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the length of a wide string (wcs)
 * @param wcs The wide string to check
 * @return <b>intmax_t</b> The length of the wide string
 * @author Nicolas TORO
 */
intmax_t my_wcslen(const wchar_t *wcs)
{
    intmax_t len = 0;

    if (wcs == NULL)
        return 0;
    while (wcs[len] != L'\0')
        len = len + 1;
    return len;
}
