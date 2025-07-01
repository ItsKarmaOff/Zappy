/*
** EPITECH PROJECT, 2025
** Zappy
** File description:
** The file containing the resource array definition
*/
/**
 * @file resource.c
 * @brief The resource.c
 * @author Christophe VANDEVOIR, Gianni TUERO, Lou PELLEGRINO,
 * Nicolas TORO, Olivier POUECH and Raphael LAUNAY
 */

#include "game.h"

const char *resources_names[RESOURCES_SIZE] = {
    "food",
    "linemate",
    "deraumere",
    "sibur",
    "mendiane",
    "phiras",
    "thystame"
};

const double resources_densities[RESOURCES_SIZE] = {
    0.5,
    0.3,
    0.15,
    0.1,
    0.1,
    0.08,
    0.05
};
