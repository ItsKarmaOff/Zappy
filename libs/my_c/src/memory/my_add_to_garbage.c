/*
** EPITECH PROJECT, 2025
** panoramix
** File description:
** The my_add_to_garbage.c
*/
/**
 * @file my_add_to_garbage.c
 * @brief The my_add_to_garbage.c
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Adds a pointer to the garbage collector
 * @note The pointer is added to the garbage collector
 * @param add The status of the garbage
 * <u>true</u> to add the pointer and <u>false</u> to remove it
 * @param ptr The pointer to add
 * @param free_func The function to free the pointer
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_add_to_garbage(bool add, void *ptr, void (*free_func)(void *))
{
    static node_t *list = NULL;
    garbage_data_t *data = NULL;

    if (add == true) {
        data = my_calloc(1, sizeof(garbage_data_t));
        data->ptr = ptr;
        data->free_func = free_func;
        AL(FALSE, my_push_front, &list, data, UNKNOWN);
        return;
    }
    for (node_t *node = list; node != NULL; node = node->next) {
        if (((garbage_data_t *)node->data)->ptr == ptr || ptr == NULL) {
            ((garbage_data_t *)node->data)->free_func(
                ((garbage_data_t *)node->data)->ptr);
        }
    }
    my_delete_list(&list);
}
