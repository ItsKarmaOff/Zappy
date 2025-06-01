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
 * @param point The point in the code where the logs are displayed
 * @author Nicolas TORO
 */
void my_point(point_t point)
{
    char *time_str = NULL;

    my_update_alloc(FALSE);
    time_str = my_get_local_time();
    my_putstr(RESET WHITE BOLD ITALIC "[");
    my_putstr(time_str);
    my_putstr("] [FILE: ");
    my_putstr(point.file);
    my_putstr(":");
    my_putnbr(point.line);
    my_putstr(", FUNCTION: ");
    my_putstr(point.func);
    my_putstr("]" RESET);
    my_putchar('\n');
    FREE(time_str);
}
