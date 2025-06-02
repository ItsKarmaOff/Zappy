/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_strstr function
*/
/**
 * @file my_strstr.c
 * @brief The file containing the my_strstr function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Search a string (to_find) on another (str)
 * and returns the address of the first occurrence
 * @param str The string to be scanned
 * @param to_find The string to search in
 * @return <b>char*</b> The address of the <u>first occurrence</u>
 * of the string to_find in the string str, <u>NULL</u> otherwise
 * @author Nicolas TORO
 */
char *my_strstr(char *str, char const *to_find)
{
    if (str == NULL || to_find == NULL)
        return NULL;
    if (my_strlen(to_find) == 0)
        return str;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (my_strncmp(&str[i], to_find, my_strlen(to_find)) == 0)
            return &str[i];
    }
    return NULL;
}
