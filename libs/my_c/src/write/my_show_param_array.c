/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_show_param_array function
*/
/**
 * @file my_show_param_array.c
 * @brief The file containing the my_show_param_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Prints the information of a parameter array (par)
 * @param par The information of the parameters
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_show_param_array(struct info_param const *par)
{
    for (int index = 0; par[index].length != 0; index++) {
        my_putstr(par[index].str);
        my_putchar('\n');
        my_putnbr(par[index].length);
        my_putchar('\n');
        my_show_word_array(par[index].word_array);
    }
}
