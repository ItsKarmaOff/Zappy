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

/* Libmy C macros */



    /* Compilation */

    /**
     * @brief A macro to disable the warnings for unused variables
     */
    #define    UNUSED __attribute__((unused))



    /* Error handling */

    /**
     * @brief Gets the string error message from errno
     */
    #define    STRERR my_strerror(errno)

    /**
     * @brief Exits the program with FAILURE exit code and message
     */
    #define    THROW(msg) my_exit(FAILURE, msg)

    /**
     * @brief Exits the program with FAILURE exit code and an exception message
     */
    #define    EXCEPTION(msg) my_exit(FAILURE, "EXCEPTION: " msg)



    /* Calculs */

    /**
     * @brief Gets the absolute value of a number
     */
    #define    ABS(value) ((value < 0) ? - value : value)

    /**
     * @brief Gets the minimum value between two numbers
     */
    #define    MIN(a, b) ((a < b) ? a : b)

    /**
     * @brief Gets the maximum value between two numbers
     */
    #define    MAX(a, b) ((a > b) ? a : b)



    /* Memory */

    /**
     * @brief Checks if a pointer is NULL
     */
    #define    IS_NULL(ptr) ((ptr) == NULL)

    /**
     * @brief Frees a pointer and sets it to NULL
     */
    #define    FREE(ptr) ptr = my_free_ptr(ptr)

    /**
     * @brief Frees a word array
     */
    #define    FREE_WORD_ARRAY(ptr) my_free_array((void **)ptr)

    /**
     * @brief Returns the length of a word array (array)
     * by traversing it to the first NULL
     */
    #define    WORD_ARRAY_LEN(array) my_word_array_len(array, SIZE_MAX, true)

    /**
     * @brief Change the malloc state and allocates memory
     * with the given function
     */
    #define    MA(type, func, ...) (my_update_malloc(type), func(__VA_ARGS__))

    /**
     * @brief Change the temporary malloc state and allocates memory
     * with the given function
     */
    #define    AL(type, func, ...) (my_update_alloc(type), func(__VA_ARGS__))

    /**
     * @brief Cast a function to a free function
     */
    #define    CAST_FREE_FUNC (void (*)(void *))



    /* Logs */

    /**
     * @brief Creates a point structure
     * with the current file, line and function
     */
    #define    POINT_STRUCT ((point_t){__FILE__, __LINE__, __func__})

    /**
     * @brief Prints a point in the code
     * with the current file, line and function
     */
    #define    POINT my_point(POINT_STRUCT)

    /**
     * @brief Prints a logs message
     */
    #define    LOG(type, message) my_logs_message(POINT_STRUCT, type, message)

    /**
     * @brief Prints an info logs message
     */
    #define    INFO(message) LOG(LOGS_NONE, message)

    /**
     * @brief Prints a debug logs message
     * @note This macro is only used if the debug mode is enabled
     */
    #define    DEBUG(message) LOG(LOGS_DEBUG, message)

    /**
     * @brief Prints an error logs message
     * @note This macro is only used if the debug mode is enabled
     */
    #define    ERROR(message) LOG(LOGS_ERROR, message)

    /**
     * @brief Prints a warning logs message
     * @note This macro is only used if the debug mode is enabled
     */
    #define    WARNING(message) LOG(LOGS_WARNING, message)



    /* String to array */

/**
* @brief A shortcut to execute str to array with default settings
* @param str The string to convert to an array
* @param type The type of separator to use
* @param separator The separator to use
* @return <b>char **</b> The array of words
*/
static inline char **my_str2array(
    const char *str, separator_type_t type, void *separator)
{
    return my_str_to_array(str, my_default_array_settings(type, separator));
}



    /* Shortcuts */

    /**
     * @brief A shortcut for the number_settings structure
     */
    #define    NB number_settings_t


    /**
     * @brief A shortcut for the current char in the format string
     * in the create str function
     */
    #define    FORMAT_CHAR str_struct->format_str[str_struct->current_index]

    /**
     * @brief Checks if a string contains a substring
     */
    #define    STR_CONTAINS(str, find) (my_strstr(str, find) != NULL) ? 1 : 0

#endif /* MACROS_H_ */
