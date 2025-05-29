/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_merge_list function
*/
/**
 * @file my_merge_list.c
 * @brief The file containing the my_merge_list function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Merges two linked lists
 * @param begin1 The beginning of the first list
 * @param begin2 The beginning of the second list
 * @param cmp The comparison function
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_merge_list(node_t **begin1, node_t *begin2, int (*cmp)())
{
    if (*begin1 == NULL) {
        *begin1 = begin2;
        return;
    }
    for (node_t *tmp = begin2; tmp != NULL; tmp = tmp->next) {
        if (my_find_node(*begin1, tmp->data, cmp) == NULL)
            my_push_back(begin1, tmp->data, tmp->type);
    }
}
