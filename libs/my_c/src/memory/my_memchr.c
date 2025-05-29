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
 * @brief Searches for the first occurrence of the character (c)
 * in the first (n) bytes of the string (s)
 * @param memory_block The memory block to search in
 * @param searched_char The character to search
 * @param size The size of the memory block
 * @return <b>void *</b> A pointer to the first occurrence of the character
 * in the memory block if found, NULL otherwise
 * @author Nicolas TORO
 */
void *my_memchr(const void *memory_block, int searched_char, uint64_t size)
{
    if (memory_block == NULL)
        return NULL;
    for (uint64_t index = 0; index < size; index++) {
        if (((char *)memory_block)[index] == searched_char)
            return (void *)&((char *)memory_block)[index];
    }
    return NULL;
}
