/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_list_size function
*/
/**
 * @file my_list_size.c
 * @brief The file containing the my_list_size function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns the size of the linked list
 * @param begin The beginning of the list
 * @return <b>size_t</b> The size of the list
 * @author Nicolas TORO
 */
size_t my_list_size(node_t const *begin)
{
    size_t nb = 0;

    for (; begin != NULL; nb++)
        begin = begin->next;
    return nb;
}
