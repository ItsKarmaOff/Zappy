/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_rev_params function
*/
/**
 * @file my_rev_params.c
 * @brief The file containing the my_rev_params function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Prints all the arguments (argc and argv) in reverse order
 * @param par The information of the parameters
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_rev_params(int argc, char **argv)
{
    for (int i = argc; i > 0; i--) {
        my_putstr(argv[i - 1]);
        my_putstr("\n");
    }
}
