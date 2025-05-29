/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_push_back function
*/
/**
 * @file my_push_back.c
 * @brief The file containing the my_push_back function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Adds a node at the end of the list
 * @param begin The beginning of the list
 * @param data The data to add
 * @param type The type of the data
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_push_back(node_t **begin, void *data, type_t type)
{
    node_t *new = my_calloc(1, sizeof(node_t));
    node_t *tmp = *begin;

    new->data = data;
    new->type = type;
    new->next = NULL;
    if (*begin == NULL) {
        new->prev = NULL;
        *begin = new;
        return;
    }
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    new->prev = tmp;
}
