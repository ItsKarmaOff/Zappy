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

    #define    BASE_2 "01"
    #define    BASE_8 "01234567"
    #define    BASE_10 "0123456789"
    #define    BASE_16_LOWERCASE "0123456789abcdef"
    #define    BASE_16_UPPERCASE "0123456789ABCDEF"

    #define    RED "\033[0;31m"
    #define    YELLOW "\033[0;33m"
    #define    BOLD "\033[1m"
    #define    UNDERLINE "\033[4m"
    #define    RESET "\033[0m"

    #define    NB_FLAGS 23
    #define    FORMAT_FLAGS "abcdefgimnopsux%AEFGNSX"
    #define    FORMAT_ATTRIBUTES "-+ #0"
    #define    FORMAT_PRECISION "."
    #define    FORMAT_NUMBERS "0123456789"

    #define    STDIN STDIN_FILENO
    #define    STDOUT STDOUT_FILENO
    #define    STDERR STDERR_FILENO

    #define    SUCCESS 0
    #define    FAILURE 84

#endif /* CONSTANTS_H_ */
