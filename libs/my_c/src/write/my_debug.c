/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_debug function
*/
/**
 * @file my_debug.c
 * @brief The file containing the my_debug function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Display a debug message
 * @param file The file name
 * @param line The line number
 * @param func The function name
 * @author Nicolas TORO
 */
void my_debug(const char *file, const int line, const char *func)
{
    my_putstr(RESET YELLOW BOLD "FILE: ");
    my_putstr(file);
    my_putstr(":");
    my_putnbr(line);
    my_putstr(RESET YELLOW ", FUNCTION: ");
    my_putstr(func);
    my_putstr(RESET);
    my_putchar('\n');
}
