/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_sort_params function
*/
/**
 * @file my_sort_params.c
 * @brief The file containing the my_sort_params function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static int check_equal(size_t len_s1, size_t len_s2,
    size_t j, size_t littlest_char_index)
{
    if (len_s1 < len_s2)
        return j;
    else if (len_s1 > len_s2)
        return littlest_char_index;
    else
        return littlest_char_index;
}

static int check_littlest(char **argv, size_t j, size_t littlest_char_index)
{
    size_t i = 0;

    while (i < my_strlen(argv[littlest_char_index])
    && i < my_strlen(argv[j])) {
        if (argv[littlest_char_index][i] < argv[j][i])
            return j;
        if (argv[littlest_char_index][i] > argv[j][i])
            return littlest_char_index;
        i++;
    }
    return check_equal(my_strlen(argv[littlest_char_index]),
    my_strlen(argv[j]), j, littlest_char_index);
}

static void check_swap(char **argv, size_t i, size_t littlest_char_index)
{
    char *temp;

    if (i != littlest_char_index) {
        temp = argv[i];
        argv[i] = argv[littlest_char_index];
        argv[littlest_char_index] = temp;
    }
}

/**
 * @brief Sorts the parameters (argc and argv) in ascending order
 * @param argc The number of parameters
 * @param argv The array of parameters
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_sort_params(int argc, char **argv)
{
    int littlest_char_index = 0;

    for (size_t i = 0; i < (size_t)argc; i++) {
        littlest_char_index = i;
        for (size_t j = i; j < (size_t)argc; j++)
            littlest_char_index = check_littlest(argv, j, littlest_char_index);
        check_swap(argv, i, littlest_char_index);
    }
    for (size_t i = argc; i > 0; i--) {
        my_putstr(argv[i - 1]);
        my_putstr("\n");
    }
}
