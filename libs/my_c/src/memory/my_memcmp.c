/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_memcmp function
*/
/**
 * @file my_memcmp.c
 * @brief The file containing the my_memcmp function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Compares the first (size) bytes
 * of the memory areas (pointer1) and (pointer2)
 * @param pointer1 The first memory area
 * @param pointer2 The second memory area
 * @param size The number of bytes to compare
 * @return <b>int</b> 0 if the memory areas are equal,
 * a positive value if the first different byte in (pointer1) is greater than
 * the corresponding byte in (pointer2), a negative value otherwise
 * @author Nicolas TORO
 */
int my_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
    if (pointer1 == NULL || pointer2 == NULL)
        return 0;
    for (size_t index = 0; index < size; index++) {
        if (((char *)pointer1)[index] != ((char *)pointer2)[index])
            return ((char *)pointer1)[index] - ((char *)pointer2)[index];
    }
    return 0;
}
