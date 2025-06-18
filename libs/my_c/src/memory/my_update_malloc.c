/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_update_malloc function
*/
/**
 * @file my_update_malloc.c
 * @brief The file containing the my_update_malloc function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief The malloc state variable
 * @note NONE (-2): Returns just the value | DEFAULT (-1): Free all
 * | FALSE (0): Basic malloc | TRUE (1): Save in garbage
 * @param set The new malloc state
 * @return <b>char</b> The malloc state
 * @author Nicolas TORO
 */
my_bool_t malloc_state(my_bool_t set)
{
    static my_bool_t state = FALSE;

    if (set != NONE)
        state = set;
    return state;
}

/**
 * @brief Updates the malloc state
 * @param type The new malloc state
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_update_malloc(my_bool_t type)
{
    malloc_state(type);
}
