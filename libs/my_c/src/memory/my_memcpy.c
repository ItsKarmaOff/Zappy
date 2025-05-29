/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_memchr function
*/
/**
 * @file my_memchr.c
 * @brief The file containing the my_memchr function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Copies (size) bytes from memory area (source)
 * to another memory area (destination)
 * @param destination The destination memory area
 * @param source The source memory area
 * @param size The number of bytes to copy
 * @return <b>void *</b> A pointer to the destination memory area
 * @author Nicolas TORO
 */
void *my_memcpy(void *destination, const void *source, uint64_t size)
{
    char *ptr = destination;
    int end = 0;

    if (destination == NULL || source == NULL)
        return NULL;
    for (uint64_t index = 0; index < size; index++) {
        if (end == 1 || ((char *)source)[index] == '\0') {
            end = 1;
            ptr[index] = '\0';
        }
        ptr[index] = ((char *)source)[index];
    }
    return (void *)ptr;
}
