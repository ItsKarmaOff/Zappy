/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The header file for the macros
*/
/**
 * @file macros.h
 * @brief The header file for the macros
 * @author Nicolas TORO
 */

#ifndef MACROS_H_
    #define MACROS_H_

    #include "functions.h"

    // Basics macros :

    #define    ABS(value) ((value < 0) ? - value : value)
    #define    MAX(a, b) ((a > b) ? a : b)
    #define    MIN(a, b) ((a < b) ? a : b)
    #define    STR_CONTAINS(str, find) (my_strstr(str, find) != NULL) ? 1 : 0
    #define    NB number_settings_t
    #define    THROW(msg) my_exit(FAILURE, msg)
    #define    EXCEPTION(msg) my_exit(FAILURE, "EXCEPTION: " msg)
    #define    UNUSED __attribute__((unused))
    #define    STRERR strerror(errno)
    #define    STR2ARRAY(str, sep, type) my_str_to_word_array(str, sep, type)
    #define    FORMAT_CHAR str_struct->format_str[str_struct->current_index]

    // Memory macros :

    #define    IS_NULL(ptr) ((ptr) == NULL)
    #define    FREE(ptr) ptr = my_free_ptr(ptr)
    #define    FREE_WORD_ARRAY(ptr) my_free_array((void **)ptr)
    #define    MA(type, func, ...) (my_update_malloc(type), func(__VA_ARGS__))
    #define    AL(type, func, ...) (my_update_alloc(type), func(__VA_ARGS__))
    #define    CAST_FREE_FUNC (void (*)(void *))

    // Logs macros :

    #define    POINT_STRUCT ((point_t){__FILE__, __LINE__, __func__})
    #define    POINT my_point(POINT_STRUCT)
    #define    LOG(type, message) my_logs_message(POINT_STRUCT, type, message)
    #define    DEBUG(message) LOG(LOGS_DEBUG, message)
    #define    ERROR(message) LOG(LOGS_ERROR, message)
    #define    WARNING(message) LOG(LOGS_WARNING, message)

#endif /* MACROS_H_ */
