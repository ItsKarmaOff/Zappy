/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strcapitalize function
*/
/**
 * @file my_strcapitalize.c
 * @brief The file containing the my_strcapitalize function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Capitalizes the first letter of each word in a string (str)
 * and lowercase the other letters
 * @param str The string to modify
 * @return <b>char*</b> The modified string
 * @author Nicolas TORO
 */
char *my_strcapitalize(char *str)
{
    str = my_strlowcase(str);
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (((str[i - 1] == '+' || str[i - 1] == '-' || str[i - 1] == ' '))
        && (str[i] >= 'a' && str[i] <= 'z'))
            str[i] = str[i] - 32;
    }
    if (str[0] >= 'a' && str[0] <= 'z')
        str[0] = str[0] - 32;
    return str;
}
