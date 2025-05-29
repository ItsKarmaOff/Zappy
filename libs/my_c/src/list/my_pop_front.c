/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_pop_front function
*/
/**
 * @file my_pop_front.c
 * @brief The file containing the my_pop_front function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Removes the first node of the list
 * @param begin The beginning of the list
 * @return <b>node_t *</b> The first node of the list
 * @author Nicolas TORO
 */
node_t *my_pop_front(node_t **begin)
{
    node_t *tmp = *begin;

    if (*begin == NULL)
        return NULL;
    *begin = (*begin)->next;
    if (*begin != NULL)
        (*begin)->prev = NULL;
    return tmp;
}
