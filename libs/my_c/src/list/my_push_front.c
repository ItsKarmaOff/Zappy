/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_push_front function
*/
/**
 * @file my_push_front.c
 * @brief The file containing the my_push_front function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
* @brief Adds a node at the beginning of the list
* @param begin The beginning of the list
* @param data The data to add
* @param type The type of the data
* @return <b>void</b>
* @author Nicolas TORO
*/
void my_push_front(node_t **begin, void *data, type_t type)
{
    node_t *new = my_calloc(1, sizeof(node_t));

    new->prev = NULL;
    new->data = data;
    new->type = type;
    new->next = *begin;
    if (*begin != NULL)
        (*begin)->prev = new;
    *begin = new;
}
