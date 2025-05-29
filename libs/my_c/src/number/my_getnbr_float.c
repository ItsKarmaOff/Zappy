/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_getnbr_float function
*/
/**
 * @file my_getnbr_float.c
 * @brief The file containing the my_getnbr_float function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static int index_negative(char const *str, int index)
{
    if (index == 0)
        return 1;
    if (str[index - 1] == '-')
        return -1;
    return 1;
}

/**
 * @brief Returns a float number starting from a string number (str)
 * @note Returns 0 if the string is not a number
 * @note The function accept only -0123456789.
 * @note The function accept only one point in the string
 * @param str The string to convert
 * @return <b>float</b> The number found in the string
 * @author Nicolas TORO
 */
float my_getnbr_float(char const *str)
{
    float convert = 0;
    int index = 0;
    float index_float = 0.1;

    if ((str[0] < '0' || str[0] > '9') && str[0] != '-')
        return 0;
    while (str[index] < '0' || str[index] > '9')
        index++;
    convert = convert * index_negative(str, index);
    for (; str[index] >= '0' && str[index] <= '9'; index++)
        convert = convert * 10 + (str[index] - 48);
    if (str[index] == '.') {
        index++;
        for (; str[index] >= '0' && str[index] <= '9'; index++) {
            convert = convert + index_float * (str[index] - 48);
            index_float = index_float * 0.1;
        }
    }
    return convert;
}
