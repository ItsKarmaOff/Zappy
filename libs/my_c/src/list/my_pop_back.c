/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_pop_back function
*/
/**
 * @file my_pop_back.c
 * @brief The file containing the my_pop_back function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Removes the last node of the list
 * @param begin The beginning of the list
 * @return <b>node_t *</b> The last node of the list
 * @author Nicolas TORO
 */
node_t *my_pop_back(node_t **begin)
{
    node_t *tmp = *begin;

    if (*begin == NULL)
        return NULL;
    for (; tmp->next != NULL; tmp = tmp->next);
    if (tmp->prev != NULL)
        tmp->prev->next = NULL;
    else
        *begin = NULL;
    return tmp;
}
