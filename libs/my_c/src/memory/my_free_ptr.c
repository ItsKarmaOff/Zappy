/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_free_ptr function
*/
/**
 * @file my_free_ptr.c
 * @brief The file containing the my_free_ptr function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Frees a pointer (ptr)
 * @param ptr The pointer to free
 * @return <b>void *</b> Always <u>NULL</u>
 * @author Nicolas TORO
 */
void *my_free_ptr(void *ptr)
{
    if (ptr == NULL)
        return NULL;
    free(ptr);
    ptr = NULL;
    return NULL;
}
