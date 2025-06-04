/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_list_to_array function
*/
/**
 * @file my_list_to_array.c
 * @brief The file containing the my_list_to_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Converts the linked list to an array
 * @param list The linked list to convert
 * @return <b>void **</b> The array created from the linked list
 * @author Nicolas TORO
 */
void **my_list_to_array(node_t *list)
{
    size_t size = my_list_size(list);
    void **array = my_calloc(size + 1, sizeof(void *));
    node_t *tmp = list;

    if (array == NULL)
        return NULL;
    for (size_t i = 0; tmp != NULL; i++) {
        array[i] = tmp->data;
        tmp = tmp->next;
    }
    array[size] = NULL;
    return array;
}
