/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_print_params function
*/
/**
 * @file my_print_params.c
 * @brief The file containing the my_print_params function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Prints all the parameters of the program
 * @param argc The number of parameters
 * @param argv The array of parameters
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_print_params(int argc, char **argv)
{
    for (size_t i = 0; i < (size_t)argc; i++) {
        my_putstr(argv[i]);
        my_putstr("\n");
    }
}
