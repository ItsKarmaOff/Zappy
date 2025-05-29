/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_show_word_array function
*/
/**
 * @file my_show_word_array.c
 * @brief The file containing the my_show_word_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Prints all word in an array (tab)
 * @param tab The array of words to print
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_show_word_array(char *const *tab)
{
    int index_tab = 0;

    if (tab == NULL)
        return;
    while (tab[index_tab] != NULL) {
        my_putstr(tab[index_tab]);
        my_putchar('\n');
        index_tab = index_tab + 1;
    }
}
