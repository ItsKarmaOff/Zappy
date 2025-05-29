/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_update_alloc function
*/
/**
 * @file my_update_alloc.c
 * @brief The file containing the my_update_alloc function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief The temporary malloc state variable
 * @note NONE (-2): Returns just the value | DEFAULT (-1): Disable the priority
 * | FALSE (0): Basic malloc | TRUE (1): Save in garbage
 * @param set The new temporary malloc state
 * @return <b>char</b> The temporary malloc state
 * @author Nicolas TORO
 */
char tmp_malloc_state(my_bool_t set)
{
    static my_bool_t state = DEFAULT;

    if (set != NONE)
        state = set;
    return state;
}

/**
 * @brief Updates the temporary malloc state
 * @param type The new temporary malloc state
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_update_alloc(char type)
{
    tmp_malloc_state(type);
}
