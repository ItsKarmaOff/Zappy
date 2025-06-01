/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_exit function
*/
/**
 * @file my_exit.c
 * @brief The file containing the my_exit function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Exits the program
 * @param status The status to return
 * @param message The message to display
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_exit(int status, char *message)
{
    if (message && status != SUCCESS)
        ERROR(message);
    else if (message)
        my_putstr(message);
    my_free();
    my_exit_asm(status);
}
