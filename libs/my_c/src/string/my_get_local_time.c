/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_get_local_time function
*/
/**
 * @file my_get_local_time.c
 * @brief The file containing the my_get_local_time function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Gets the local time
 * @return <b>char *</b> The local time as a string
 * @author Nicolas TORO
 */
char *my_get_local_time(void)
{
    struct timeval tv;
    struct tm *tm_info;
    char temp[DATE_SIZE] = {0};
    char *result = NULL;

    gettimeofday(&tv, NULL);
    tm_info = localtime(&tv.tv_sec);
    strftime(temp, sizeof(temp), DATE_FORMAT, tm_info);
    result = my_calloc(ADDITIONAL_DATE_SIZE, sizeof(char));
    snprintf(result, ADDITIONAL_DATE_SIZE, ADDITIONAL_DATE_FORMAT,
        temp, tv.tv_usec / 1000);
    return result;
}
