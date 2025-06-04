/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_program_destroy function
*/
/**
 * @file my_program_destroy.c
 * @brief The file containing the my_program_destroy function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Destroys the program by calling the provided destroy function
 * @note If the destroy function is NULL,
 * it will call the destroy function set previously.
 * If the program is already destroyed, it will do nothing.
 * @param destroy_func The function to call to destroy the program
 * @author Nicolas TORO
 */
void my_program_destroy(void (*destroy_func)(void *ptr))
{
    static bool is_destroyed = false;
    static void (*destroy_function)(void *) = NULL;

    if (is_destroyed)
        return;
    if (destroy_func != NULL) {
        destroy_function = destroy_func;
        return;
    }
    if (destroy_function != NULL) {
        destroy_function(NULL);
        is_destroyed = true;
    }
}
