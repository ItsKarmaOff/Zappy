/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The function to resize an allocated memory block.
*/
/**
 * @file my_resize_alloc.c
 * @brief The function to resize an allocated memory block.
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Resize an allocated memory block.
 * @param ptr Pointer to the previously allocated memory block.
 * @param old_size Size of the previously allocated memory block.
 * @param new_size New size for the memory block.
 * @return Pointer to the resized memory block, or NULL if new_size is 0.
 */
void *my_resize_alloc(void *ptr, size_t old_size, size_t new_size)
{
    void *new_ptr = NULL;

    if (new_size == 0) {
        FREE(ptr);
        return NULL;
    }
    if (ptr == NULL) {
        return my_calloc(1, new_size);
    }
    if (old_size == new_size) {
        return ptr;
    }
    new_ptr = my_calloc(1, new_size);
    my_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
    FREE(ptr);
    return new_ptr;
}
