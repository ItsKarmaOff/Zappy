/*
** EPITECH PROJECT, 2024
** Libmy
** File description:
** The file containing the my_get_number function
*/
/**
 * @file my_get_number.c
 * @brief The file containing the my_get_number function
 * @author Nicolas TORO
 */

#include "../../include/my.h"

int my_errno;

static bool not_a_number(char c)
{
    if ((c < '0' || c > '9') && c != '-' && c != '+')
            return true;
    return false;
}

static char check_end(char *number, number_settings_t *settings,
    ssize_t i, ssize_t start)
{
    my_errno = 0;
    if ((!settings->letter_before && not_a_number(number[i]) && start == -1)
    || (!settings->letter_after && not_a_number(number[i]) && start != -1)
    || (!settings->letter_after && (number[i] == '-' || number[i] == '+')
    && start != -1)
    || (!settings->multiple_signe && i != 0 && (number[i] == '-' ||
    number[i] == '+') && (number[i - 1] == '-' || number[i - 1] == '+'))
    || (!settings->overflow && (i > start + 9 ||
    (i > start + 8 && number[start] != '1' && number[start] != '2')))) {
        my_errno = 1;
        return 1;
    }
    if (settings->letter_after && not_a_number(number[i]) && start != -1)
        return 1;
    return 0;
}

/**
 * @brief Returns an int number starting from a string number (number)
 * and change my_errno if an error occurs depending on the settings (settings)
 * @note The function will change <u>my_errno</u> by 1 if an error occurs
 * depending on the settings you choose with the <b>settings</b> parameter
 * @param number The string to convert
 * @param settings The settings of the function
 * @return <b>intmax_t</b> The number found in the string
 * @author Nicolas TORO
 */
intmax_t my_get_number(char *number, number_settings_t settings)
{
    int64_t nb = 0;
    ssize_t start = -1;
    int8_t neg = 1;

    if (number[0] == '\0')
        return nb;
    for (ssize_t i = 0; number[i] != '\0'; i++) {
        if (check_end(number, &settings, i, start))
            return nb * neg;
        if ((settings.letter_before && not_a_number(number[i]) && start == -1)
        || (settings.letter_after && not_a_number(number[i]) && start != -1))
            neg = 1;
        if (number[i] == '-' && start == -1)
            neg = neg * -1;
        if (start == -1 && number[i] >= '1' && number[i] <= '9')
            start = i;
        if (number[i] >= '0' && number[i] <= '9')
            nb = nb * 10 + (number[i] - 48);
    }
    return nb * neg;
}
