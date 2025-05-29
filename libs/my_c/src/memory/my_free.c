/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_free function
*/
/**
 * @file my_free.c
 * @brief The file containing the my_free function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Free allocated memory in the garbage collector
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_free(void)
{
    malloc_state(DEFAULT);
    my_malloc(0);
}
