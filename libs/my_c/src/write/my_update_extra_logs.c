/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_update_extra_logs function
*/
/**
 * @file my_update_extra_logs.c
 * @brief The file containing the my_update_extra_logs function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief The extra logs variable
 * @note NONE (-2) and DEFAULT (-1): Returns just the value |
 * FALSE (0): Extra logs disable | TRUE (1): Extra logs enable
 * @param set The extra logs state
 * @return <b>my_bool_t</b> The extra logs state
 * @author Nicolas TORO
 */
my_bool_t extra_logs(my_bool_t set)
{
    static my_bool_t state = FALSE;

    if (set != NONE)
        state = set;
    return state;
}

/**
 * @brief Updates the extra logs state
 * @param type The new extra logs state
 * @return <b>void</b>
 * @author Nicolas TORO
 */
void my_update_extra_logs(my_bool_t type)
{
    extra_logs(type);
}
