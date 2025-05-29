/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_printf function
*/
/**
 * @file my_printf.c
 * @brief The file containing the my_printf function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Print a formatted string
 * @param format The format string
 * @param ... The arguments to replace in the format string
 * @return <b>intmax_t</b> The length of the string
 * @author Nicolas TORO
 */
intmax_t my_printf(char const *format, ...)
{
    va_list args;
    char *result_str = NULL;
    intmax_t len = 0;
    my_bool_t malloc_backup = malloc_state(NONE);
    my_bool_t tmp_malloc_backup = tmp_malloc_state(NONE);

    tmp_malloc_state(DEFAULT);
    malloc_state(FALSE);
    va_start(args, format);
    result_str = my_create_str_va(format, args);
    va_end(args);
    if (result_str == NULL)
        return -1;
    len = my_strlen(result_str);
    write(1, result_str, len);
    free(result_str);
    tmp_malloc_state(tmp_malloc_backup);
    malloc_state(malloc_backup);
    return len;
}
