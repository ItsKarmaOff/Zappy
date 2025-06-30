/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_get_time function
*/
/**
 * @file my_get_time.c
 * @brief The file containing the my_get_time function
 * @author Nicolas TORO
 */

#include "my.h"

/**
 * @brief Gets the current time using CLOCK_MONOTONIC
 * @return <b>timespec_t</b> The current time
 */
timespec_t my_get_time(void)
{
    timespec_t time;

    if (clock_gettime(CLOCK_MONOTONIC, &time) == -1)
        THROW(my_create_str("EXCEPTION: clock_gettime failed: %s", STRERR));
    return time;
}
