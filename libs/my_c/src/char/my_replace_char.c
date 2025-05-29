/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_replace_char function
*/
/**
 * @file my_replace_char.c
 * @brief The file containing the my_replace_char function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Replace a char in a string by another char
 * @param str The string to modify
 * @param to_replace The char to replace
 * @param replace_by The char to replace by
 * @return <b>void</b>
 */
void my_replace_char(char *str, char to_replace, char replace_by)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_replace)
            str[i] = replace_by;
    }
}
