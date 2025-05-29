/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_putchar function
*/
/**
 * @file my_putchar.c
 * @brief The file containing the my_putchar function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Prints a char (c) in the stdout
 * @param c The char to print
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_putchar(char c)
{
    write(1, &c, 1);
}
