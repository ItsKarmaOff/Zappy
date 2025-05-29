/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_params_to_array function
*/
/**
 * @file my_params_to_array.c
 * @brief The file containing the my_params_to_array function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

/**
 * @brief Returns a info_params struct of the argc (ac) and the argv (av)
 * @param ac The number of parameters
 * @param av The array of parameters
 * @return <b>struct info_param*</b> The information of the parameters
 * @author Nicolas TORO
 */
struct info_param *my_params_to_array(int ac, char **av)
{
    struct info_param *result;
    int i = 0;

    result = my_calloc(ac + 1, sizeof(struct info_param));
    for (; i < ac; i++) {
        result[i].length = my_strlen(av[i]);
        result[i].str = av[i];
        result[i].copy = my_strdup(av[i]);
        result[i].word_array = STR2ARRAY(av[i], "", DEFAULT_SEPARATOR);
    }
    result[i].length = 0;
    result[i].str = 0;
    result[i].copy = 0;
    result[i].word_array = 0;
    return result;
}
