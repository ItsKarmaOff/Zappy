/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_memmove function
*/
/**
 * @file my_memmove.c
 * @brief The file containing the my_memmove function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Move (size) bytes from memory area (source)
 * to another memory area (destination)
 * @param destination The destination memory area
 * @param source The source memory area
 * @param size The number of bytes to move
 * @return <b>void *</b> A pointer to the destination memory area
 * @author Nicolas TORO
 */
void *my_memmove(void *destination, const void *source, size_t size)
{
    char *ptr = destination;
    bool end = false;

    if (destination == NULL || source == NULL)
        return NULL;
    for (size_t index = 0; index < size; index++) {
        if (end == true || ((char *)source)[index] == '\0') {
            end = true;
            ptr[index] = '\0';
        }
        ptr[index] = ((char *)source)[index];
    }
    return (void *)ptr;
}
