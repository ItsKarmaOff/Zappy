/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_difftime function
*/
/**
 * @file my_difftime.c
 * @brief The file containing the my_difftime function
 * @author Nicolas TORO
 */

#include "my.h"

/**
 * @brief Calculates the difference in seconds between two timespec_t
 * @param end The end time
 * @param start The start time
 * @return <b>double</b> The difference in seconds
 * @author Nicolas TORO
 */
double my_difftime(timespec_t end, timespec_t start)
{
    double seconds = (double)(end.tv_sec - start.tv_sec);
    double nanoseconds = (double)(end.tv_nsec - start.tv_nsec) * 1e-9;

    return seconds + nanoseconds;
}
