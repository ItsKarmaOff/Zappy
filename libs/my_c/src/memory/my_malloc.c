/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_malloc function
*/
/**
 * @file my_malloc.c
 * @brief The file containing the my_malloc function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Allocates memory for a certain size
 * @note If the allocation fails, it throws an error and exits the program
 * @param size The size of the memory to allocate
 * @return <b>void *</b> A pointer to the allocated memory
 * @author Nicolas TORO
 */
void *my_secure_malloc(size_t size)
{
    void *ptr = NULL;

    if (size == 0)
        THROW("my_malloc: Allocating 0 bytes\n");
    ptr = malloc(size);
    if (ptr == NULL && size != 0)
        THROW("my_malloc: Not enough memory to allocate\n");
    return ptr;
}

/**
 * @brief Allocates memory for an array of bytes (size)
 * @note If the allocation fails, it throws an error and exits the program
 * @note The allocation type is defined by the malloc state,
 * or by the temporary malloc state if it is defined
 * @param size The size of the memory to allocate
 * @return <b>void *</b> A pointer to the allocated memory
 * @author Nicolas TORO
 */
void *my_malloc(size_t size)
{
    static node_t *list = NULL;
    void *ptr = NULL;
    char state = malloc_state(NONE);

    if (tmp_malloc_state(NONE) != -1) {
        state = tmp_malloc_state(NONE);
        tmp_malloc_state(DEFAULT);
    }
    if (state == TRUE) {
        ptr = my_secure_malloc(size);
        AL(FALSE, my_push_front, &list, ptr, VOID);
        return ptr;
    }
    if (state == FALSE)
        return my_secure_malloc(size);
    if (state == DEFAULT)
        my_delete_list(&list);
    return NULL;
}
