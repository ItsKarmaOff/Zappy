/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The tests.c
*/
/**
 * @file tests.c
 * @brief The tests.c
 * @author Nicolas TORO
 */

#include "tests.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}