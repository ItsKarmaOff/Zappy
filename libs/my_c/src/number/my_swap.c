/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_swap function
*/
/**
 * @file my_swap.c
 * @brief The file containing the my_swap function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Swaps two integers (a) and (b)
 * @param a The first integer
 * @param b The second integer
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_swap(int *a, int *b)
{
    int c;

    c = *a;
    *a = *b;
    *b = c;
}
