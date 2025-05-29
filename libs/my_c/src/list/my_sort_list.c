/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_sort_list function
*/
/**
 * @file my_sort_list.c
 * @brief The file containing the my_sort_list function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

static void check_swap(node_t **list, int (*cmp)())
{
    void *tmp;

    if ((*list)->prev != NULL && cmp((*list)->prev->data, (*list)->data) > 0) {
        tmp = (*list)->prev->data;
        (*list)->prev->data = (*list)->data;
        (*list)->data = tmp;
    }
}

/**
 * @brief Sorts the linked list
 * @param begin The beginning of the list
 * @param cmp The comparison function
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_sort_list(node_t **begin, int (*cmp)())
{
    for (node_t *list1 = *begin; list1 != NULL; list1 = list1->next) {
        for (node_t *list2 = (*begin)->next;
        list2 != NULL; list2 = list2->next)
            check_swap(&list2, cmp);
    }
}
