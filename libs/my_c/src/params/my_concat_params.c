/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_concat_params function
*/
/**
 * @file my_concat_params.c
 * @brief The file containing the my_concat_params function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns a string with all the arguments (argc and argv) concatenated
 * @param argc The number of parameters
 * @param argv The array of parameters
 * @return <b>char*</b> The concatenated string of the parameters
 * @author Nicolas TORO
 */
char *my_concat_params(int argc, char **argv)
{
    char *result;
    size_t len_result = 0;

    for (size_t i = 0; i < (size_t)argc; i++)
        len_result = len_result + my_strlen(argv[i]);
    result = my_calloc(len_result + argc, sizeof(char));
    for (size_t j = 0; j < (size_t)argc; j++) {
        result = my_strcat(result, argv[j]);
        result = my_strcat(result, "\n");
    }
    result[len_result + argc] = '\0';
    return result;
}
