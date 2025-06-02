/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_get_node_at_index function
*/
/**
 * @file my_get_node_at_index.c
 * @brief The file containing the my_get_node_at_index function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Gets the node at the specified index in a linked list
 * @param begin The beginning of the list
 * @param index The index of the node to get
 * @return <b>node_t *</b> The node at the specified index or NULL if not found
 * @author Nicolas TORO
 */
node_t *my_get_node_at_index(node_t *begin, size_t index)
{
    node_t *tmp = begin;

    if (begin == NULL)
        return NULL;
    for (size_t current_index = 0; tmp != NULL; current_index++) {
        if (current_index == index)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
