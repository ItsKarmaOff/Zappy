/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_concat_list function
*/
/**
 * @file my_concat_list.c
 * @brief The file containing the my_concat_list function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Concatenates two linked lists
 * @param begin1 The beginning of the first list
 * @param begin2 The beginning of the second list
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_concat_list(node_t **begin1, node_t *begin2)
{
    node_t *tmp = *begin1;

    if (*begin1 == NULL) {
        *begin1 = begin2;
        return;
    }
    for (; tmp->next != NULL; tmp = tmp->next);
    tmp->next = begin2;
    begin2->prev = tmp;
}
