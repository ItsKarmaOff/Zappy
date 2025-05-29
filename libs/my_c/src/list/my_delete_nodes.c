/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_delete_nodes function
*/
/**
 * @file my_delete_nodes.c
 * @brief The file containing the my_delete_nodes function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void remove_node(node_t **begin, node_t *tmp)
{
    if (tmp->prev != NULL)
        tmp->prev->next = tmp->next;
    else
        *begin = tmp->next;
    if (tmp->next != NULL)
        tmp->next->prev = tmp->prev;
    if (tmp->type != UNKNOWN)
        FREE(tmp->data);
    FREE(tmp);
}

/**
 * @brief Deletes nodes from a linked list
 * @param begin The beginning of the list
 * @param data_ref The data to delete
 * @param cmp The comparison function
 * @return <b>int</b> The number of nodes deleted from the list
 * @author Nicolas TORO
 */
int my_delete_nodes(node_t **begin, void const *data_ref, int (*cmp)())
{
    node_t *tmp = *begin;
    node_t *next = NULL;
    int nodes_deleted = 0;

    while (tmp != NULL) {
        next = tmp->next;
        if ((cmp == NULL && tmp->data == data_ref)
        || (cmp != NULL && cmp(tmp->data, data_ref) == 0)) {
            remove_node(begin, tmp);
            nodes_deleted++;
        }
        tmp = next;
    }
    return nodes_deleted;
}
