/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_memset function
*/
/**
 * @file my_memset.c
 * @brief The file containing the my_memset function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Fills the first (size) bytes of the memory area pointed (pointer)
 * with a constant byte (value)
 * @param pointer The memory area to fill
 * @param value The byte to fill the memory area with
 * @param size The number of bytes to fill
 * @return <b>void *</b> A pointer to the memory area
 * @author Nicolas TORO
 */
void *my_memset(void *pointer, int value, uint64_t size)
{
    if (pointer == NULL)
        return NULL;
    for (uint64_t i = 0; i < size; i++)
        ((char *)pointer)[i] = value;
    return pointer;
}
