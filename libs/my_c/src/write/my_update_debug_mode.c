/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_update_debug_mode function
*/
/**
 * @file my_update_debug_mode.c
 * @brief The file containing the my_update_debug_mode function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief The debug mode variable
 * @note NONE (-2) and DEFAULT (-1): Returns just the value |
 * FALSE (0): Debug mode disable | TRUE (1): Debug mode enable
 * @param set The debug mode state
 * @return <b>my_bool_t</b> The debug mode state
 * @author Nicolas TORO
 */
my_bool_t debug_mode(my_bool_t set)
{
    static my_bool_t state = FALSE;

    if (set != NONE)
        state = set;
    return state;
}

/**
 * @brief Updates the debug mode
 * @param type The new debug mode state
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_update_debug_mode(my_bool_t type)
{
    debug_mode(type);
}
