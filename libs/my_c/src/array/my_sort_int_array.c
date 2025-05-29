/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_sort_int_array function
*/
/**
 * @file my_sort_int_array.c
 * @brief The file containing the my_sort_int_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void sort_tab(int *array, int i, int j)
{
    int temp = 0;

    if (array[j] < array[i]) {
        temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

/**
 * @brief Sorts an array (array) with a defined size (size)
 * of integers in ascending order
 * @param tab The array to sort
 * @param size The size of the tab
 * @author Nicolas TORO
 */
void my_sort_int_array(int *array, int size)
{
    if (array == NULL)
        return;
    for (int i = 0; i <= size; i++) {
        for (int j = i + 1; j < size; j++) {
            sort_tab(array, i, j);
        }
    }
}
