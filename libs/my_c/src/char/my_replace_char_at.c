/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_replace_char_at function
*/
/**
 * @file my_replace_char_at.c
 * @brief The file containing the my_replace_char_at function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Replace a char in a string by another char at a specific occurrence
 * @param str The string to modify
 * @param to_replace The char to replace
 * @param replace_by The char to replace by
 * @param occurrence The occurrence of the char to replace
 * @return <b>void</b>
 */
void my_replace_char_at(char *str, char to_replace, char replace_by,
    size_t occurrence)
{
    size_t count = 0;

    if (str == NULL || occurrence == 0)
        return;
    for (size_t i = 0; str[i] != '\0'; i++) {
        if (str[i] == to_replace)
            count++;
        if (str[i] == to_replace && count == occurrence) {
            str[i] = replace_by;
            return;
        }
    }
}
