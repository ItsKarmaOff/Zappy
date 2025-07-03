/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_close function
*/
/**
 * @file my_close.c
 * @brief The file containing the my_close function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Closes a file descriptor (fd)
 * @note Used for the garbage collector
 * @param fd The file descriptor to close
 */
void my_close(void *fd)
{
    int *file_descriptor = (int *)fd;

    if (file_descriptor == NULL)
        return;
    close(*file_descriptor);
}
