/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The my_close.c
*/
/**
 * @file my_close.c
 * @brief The my_close.c
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