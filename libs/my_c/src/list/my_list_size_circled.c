/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_list_siz_circled function
*/
/**
 * @file my_list_size_circled.c
 * @brief The file containing the my_list_siz_circled function
 * @author Gianni TUERO
 */

#include "../../include/my.h"

/**
 * @brief Returns the size of the linked list
 * @param begin The beginning of the list
 * @return <b>size_t</b> The size of the list
 * @author Nicolas TORO
 */
size_t my_list_size_circled(node_t const *begin)
{
    size_t nb = 0;

    for (node_t const *tmp = begin; tmp != NULL; tmp = tmp->next) {
        nb++;
        if (tmp->next == begin)
            break;
    }
    return nb;
}
