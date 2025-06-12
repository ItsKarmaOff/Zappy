/*
** EPITECH PROJECT, 2025
** Libmy
** File description:
** The file containing the my_logs_message function
*/
/**
 * @file my_logs_message.c
 * @brief The file containing the my_logs_message function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/* The logs type strings */
const char *logs_type_strings[] = {
    "",
    "DEBUG",
    "WARNING",
    "ERROR"
};

/* The logs type colors */
const char *logs_type_colors[] = {
    "",
    YELLOW,
    MAGENTA,
    RED
};

/**
 * @brief Display a logs message
 * @param point The point in the code where the logs are displayed
 * @param type The type of logs message
 * @param message The message to display
 */
void my_logs_message(point_t point, logs_type_t type, const char *message)
{
    if (type == LOGS_NONE && extra_logs(NONE) == TRUE) {
        if (debug_mode(NONE) == TRUE)
            my_point(point);
        my_putstr(message);
        my_putstr(RESET);
        return;
    }
    if ((type != LOGS_NONE) &&
    (type != LOGS_DEBUG || debug_mode(NONE) == TRUE)) {
        if (debug_mode(NONE) == TRUE)
            my_point(point);
        my_putstr(logs_type_colors[type]);
        my_putchar('[');
        my_putstr(logs_type_strings[type]);
        my_putstr("] ");
        my_putstr(message);
        my_putstr(RESET);
    }
}
