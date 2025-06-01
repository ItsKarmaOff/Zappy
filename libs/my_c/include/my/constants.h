/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The header file for the constants
*/
/**
 * @file constants.h
 * @brief The header file for the constants
 * @author Nicolas TORO
 */

#ifndef CONSTANTS_H_
    #define CONSTANTS_H_

    /* Include standard libraries */

    #include <dirent.h>
    #include <errno.h>
    #include <fcntl.h>
    #include <float.h>
    #include <glob.h>
    #include <limits.h>
    #include <math.h>
    #include <signal.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/wait.h>
    #include <tgmath.h>
    #include <time.h>
    #include <unistd.h>
    #include <netinet/in.h>
    #include <sys/time.h>



    /* Maximum and minimum values for various data types */

    #define    MAX_SHORT_SHORT 127
    #define    MIN_SHORT_SHORT -128
    #define    MAX_SHORT 32767
    #define    MIN_SHORT -32768
    #define    MAX_INT 2147483647
    #define    MIN_INT -2147483648
    #define    MAX_LONG 9223372036854775807
    #define    MIN_LONG -9223372036854775808
    #define    MAX_SIZE_T 18446744073709551615
    #define    MAX_FLOAT 3.402823466e+38f
    #define    MIN_FLOAT -3.402823466e+38f
    #define    MAX_DOUBLE 1.7976931348623158e+308
    #define    MIN_DOUBLE -1.7976931348623158e+308
    #define    MAX_LONG_DOUBLE 1.189731e+4932L
    #define    MIN_LONG_DOUBLE 3.362103e-4932L



    /* Base characters for number systems */

    #define    BASE_2 "01"
    #define    BASE_8 "01234567"
    #define    BASE_10 "0123456789"
    #define    BASE_16_LOWERCASE "0123456789abcdef"
    #define    BASE_16_UPPERCASE "0123456789ABCDEF"



    /* Colors and formatting for terminal output */

    #define    RESET "\033[0m"
    #define    BLACK "\033[0;30m"
    #define    RED "\033[0;31m"
    #define    GREEN "\033[0;32m"
    #define    YELLOW "\033[0;33m"
    #define    BLUE "\033[0;34m"
    #define    MAGENTA "\033[0;35m"
    #define    CYAN "\033[0;36m"
    #define    WHITE "\033[0;37m"
    #define    LIGHT_GREY "\033[0;37m"
    #define    DARK_GREY "\033[0;90m"
    #define    BOLD "\033[1m"
    #define    ITALIC "\033[3m"
    #define    UNDERLINE "\033[4m"
    #define    BLINK "\033[5m"
    #define    REVERSE "\033[7m"
    #define    HIDDEN "\033[8m"



    /* my_create_str function constants */

    #define    NB_FLAGS 23
    #define    FORMAT_FLAGS "abcdefgimnopsux%AEFGNSX"
    #define    FORMAT_ATTRIBUTES "-+ #0"
    #define    FORMAT_PRECISION "."
    #define    FORMAT_NUMBERS "0123456789"



    /* File descriptors for standard input/output */

    #define    STDIN STDIN_FILENO
    #define    STDOUT STDOUT_FILENO
    #define    STDERR STDERR_FILENO



    /* Exit codes for success and failure */

    #define    SUCCESS 0
    #define    FAILURE 84



    /* Date */

    #define    DATE_FORMAT "%Y-%m-%d %H:%M:%S"
    #define    ADDITIONAL_DATE_FORMAT "%s.%03ld"
    #define    DATE_SIZE 20
    #define    ADDITIONAL_DATE_SIZE (DATE_SIZE + 4)

#endif /* CONSTANTS_H_ */
