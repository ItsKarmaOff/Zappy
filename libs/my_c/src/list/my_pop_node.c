/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_pop_node function
*/
/**
 * @file my_pop_node.c
 * @brief The file containing the my_pop_node function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void change_list(node_t **begin, node_t *tmp)
{
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    else
        *begin = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
}

/**
 * @brief Removes a node from the list
 * @param begin The beginning of the list
 * @param data_ref The data to remove
 * @param cmp The comparison function
 * @return <b>node_t *</b> The node removed from the list
 * @author Nicolas TORO
 */
node_t *my_pop_node(node_t **begin, void const *data_ref, int (*cmp)())
{
    node_t *tmp = *begin;
    node_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if ((cmp == NULL && tmp->data == data_ref)
        || (cmp != NULL && cmp(tmp->data, data_ref) == 0)) {
            change_list(begin, tmp);
            return tmp;
        }
        tmp = next;
    }
    return NULL;
}
