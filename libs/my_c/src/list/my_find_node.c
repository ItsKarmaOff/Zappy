/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_find_node function
*/
/**
 * @file my_find_node.c
 * @brief The file containing the my_find_node function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Finds a node in the linked list
 * @param begin The beginning of the list
 * @param data The data to find
 * @param cmp The comparison function
 * @return <b>node_t *</b> The node found in the list
 * @author Nicolas TORO
 */
node_t *my_find_node(node_t const *begin, void const *data_ref, int (*cmp) ())
{
    for (node_t *tmp = (node_t *)begin; tmp != NULL; tmp =
        tmp->next) {
        if ((cmp == NULL && tmp->data == data_ref)
        || (cmp != NULL && cmp(tmp->data, data_ref) == 0))
            return tmp;
    }
    return NULL;
}
