/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_rev_list function
*/
/**
 * @file my_rev_list.c
 * @brief The file containing the my_rev_list function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Reverses the linked list
 * @param begin The beginning of the list
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_rev_list(node_t **begin)
{
    node_t *previous_list = NULL;
    node_t *current_list = *begin;
    node_t *next_list = NULL;

    while (current_list != NULL) {
        next_list = current_list->next;
        current_list->next = previous_list;
        current_list->prev = next_list;
        previous_list = current_list;
        current_list = next_list;
    }
    *begin = previous_list;
}
