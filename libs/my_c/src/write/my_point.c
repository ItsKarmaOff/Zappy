/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_point function
*/
/**
 * @file my_point.c
 * @brief The file containing the my_point function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Display a  point in the code
 * @note This function use the temporary malloc state
 * @param file The file name
 * @param line The line number
 * @param func The function name
 * @author Nicolas TORO
 */
void my_point(const char *file, const int line, const char *func)
{
    char *time_str = NULL;

    my_update_alloc(FALSE);
    time_str = my_get_local_time();
    my_putstr(RESET WHITE BOLD ITALIC "[");
    my_putstr(time_str);
    my_putstr("] [FILE: ");
    my_putstr(file);
    my_putstr(":");
    my_putnbr(line);
    my_putstr(", FUNCTION: ");
    my_putstr(func);
    my_putstr("]" RESET);
    my_putchar('\n');
    FREE(time_str);
}
