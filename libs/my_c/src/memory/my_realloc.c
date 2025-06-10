/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_realloc function
*/
/**
 * @file my_realloc.c
 * @brief The file containing the my_realloc function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Reallocates memory block
 * @param pointer The pointer to the memory block
 * @param size The new size of the memory block
 * @return <b>void *</b> A pointer to the new memory block
 * @author Nicolas TORO
 */
void *my_realloc(void *pointer, size_t size)
{
    void *ptr = my_malloc(size);

    if (ptr != NULL)
        my_memcpy(ptr, pointer, size);
    return ptr;
}
