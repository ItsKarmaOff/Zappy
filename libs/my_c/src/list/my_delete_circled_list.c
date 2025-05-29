/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_delete_circle_list function
*/
/**
 * @file my_delete_circle_list.c
 * @brief The file containing the my_delete_circle_list function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Deletes a circular linked list
 * @param begin The beginning of the list
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_delete_circle_list(node_t **begin)
{
    node_t *backup = *begin;
    node_t *tmp = NULL;
    node_t *next = NULL;

    if (backup != NULL)
        tmp = backup->next;
    while (tmp != backup && tmp != NULL) {
        next = tmp->next;
        if (tmp->data != NULL && tmp->type != UNKNOWN)
            FREE(tmp->data);
        FREE(tmp);
        tmp = next;
    }
    if (backup != NULL) {
        if (backup->data != NULL && backup->type != UNKNOWN)
            FREE(backup->data);
        FREE(backup);
    }
    *begin = NULL;
}
