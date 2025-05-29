/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_params_to_list function
*/
/**
 * @file my_params_to_list.c
 * @brief The file containing the my_params_to_list function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Creates a linked list from the arguments (argc and argv)
 * @param ac The number of arguments
 * @param av The array of arguments
 * @return <b>node_t *</b> The linked list created from the array of strings
 * @author Nicolas TORO
 */
node_t *my_params_to_list(int ac, char *const *av)
{
    node_t *list = my_calloc(1, sizeof(node_t));

    list->prev = NULL;
    list->data = my_strdup(av[0]);
    list->type = STRING;
    list->next = NULL;
    for (int arg = 1; arg < ac; arg++)
        my_push_front(&list, my_strdup(av[arg]), STRING);
    return list;
}
