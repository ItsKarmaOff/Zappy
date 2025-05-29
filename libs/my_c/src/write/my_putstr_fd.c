/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_putstr_fd function
*/
/**
 * @file my_putstr_fd.c
 * @brief The file containing the my_putstr_fd function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Writes a string (str) in a file descriptor (fd)
 * and returns the length of the printed string
 * @param str The string to print
 * @param fd The file descriptor to write in
 * @return <b>int</b> The number of printed characters
 * @author Nicolas TORO
 */
int my_putstr_fd(char const *str, int fd)
{
    int len;

    if (str == NULL || fd < 0)
        return 0;
    len = my_strlen(str);
    write(fd, str, len);
    return len;
}
