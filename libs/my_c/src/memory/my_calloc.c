/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_calloc function
*/
/**
 * @file my_calloc.c
 * @brief The file containing the my_calloc function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Allocates memory and initializes all the bytes to 0
 * @param element_count The number of elements
 * @param element_size The size of each element
 * @return <b>void *</b> A pointer to the allocated memory
 * @author Nicolas TORO
 */
void *my_calloc(size_t element_count, size_t element_size)
{
    void *ptr = my_malloc(element_count * element_size);

    if (ptr != NULL)
        my_memset(ptr, 0, element_count * element_size);
    return ptr;
}
