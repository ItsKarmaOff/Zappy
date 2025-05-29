/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_list_to_array_circled function
*/
/**
 * @file my_list_to_array.c
 * @brief The file containing the my_list_to_array_circled function
 * @author Gianni TUERO
 */

#include "../../include/my.h"

/**
 * @brief Converts the circular linked list to an array
 * @param list The circular linked list to convert
 * @return <b>void **</b> The array created from the circular linked list
 */
void **my_list_to_array_circled(node_t **list)
{
    int size = my_list_size_circled(*list);
    void **array = my_calloc(size + 1, sizeof(void *));
    node_t *tmp = *list;

    if (array == NULL)
        return NULL;
    for (int i = 0; tmp != NULL; i++) {
        array[i] = tmp->data;
        tmp = tmp->next;
        if (tmp == *list)
            break;
    }
    array[size] = NULL;
    return array;
}
