/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The teams.c
*/
/**
 * @file teams.c
 * @brief The teams.c
 * @author Nicolas TORO
 */

#include "game.h"

team_t *create_team(const char *name)
{
    team_t *team = my_calloc(1, sizeof(team_t));

    team->name = name;
    return team;
}
