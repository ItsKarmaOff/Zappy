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
node_t *my_get_node_at_index(node_t *begin, int index)
{
    node_t *tmp = begin;
    int current_index = 0;

    if (begin == NULL || index < 0)
        return NULL;
    while (tmp != NULL) {
        if (current_index == index)
            return tmp;
        tmp = tmp->next;
        current_index++;
    }
    return NULL;
}
