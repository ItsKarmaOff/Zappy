/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_push_back_circled function
*/
/**
 * @file my_push_back_circled.c
 * @brief The file containing the my_push_back_circled function
 * @author Gianni TUERO
 */

#include "../../include/my.h"

/**
* @brief Adds a node at the beginning of the circular linked list
* @param begin The beginning of the list
* @param data The data to add
* @param type The type of the data
* @return <b>void</b>
*/
void my_push_back_circled(node_t **begin, void *data, type_t type)
{
    node_t *new = my_calloc(1, sizeof(node_t));
    node_t *tmp = *begin;

    new->data = data;
    new->type = type;
    if (*begin == NULL) {
        new->prev = NULL;
        new->next = NULL;
        *begin = new;
        return;
    }
    for (; tmp->next != NULL && tmp->next != *begin; tmp = tmp->next);
    tmp->next = new;
    new->prev = tmp;
    new->next = *begin;
    (*begin)->prev = new;
}
