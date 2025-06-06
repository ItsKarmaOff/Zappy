/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_delete_list function
*/
/**
 * @file my_delete_list.c
 * @brief The file containing the my_delete_list function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Deletes the linked list
 * @param begin The beginning of the list
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_delete_list(node_t **begin)
{
    node_t *tmp = *begin;
    node_t *next = NULL;

    while (tmp != NULL) {
        next = tmp->next;
        if (tmp->data != NULL &&
        tmp->type != UNKNOWN && tmp->type != ARRAY_OF_STRING)
            FREE(tmp->data);
        if (tmp->data != NULL && tmp->type == ARRAY_OF_STRING)
            my_free_array(tmp->data);
        FREE(tmp);
        tmp = next;
    }
    *begin = NULL;
}
