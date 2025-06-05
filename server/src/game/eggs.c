/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The eggs.c
*/
/**
 * @file eggs.c
 * @brief The eggs.c
 * @author Nicolas TORO
 */

#include "game.h"

egg_t *create_egg(game_t *game)
{
    egg_t *egg = AL(FALSE, my_calloc, 1, sizeof(egg_t));

    egg->id = game->game_settings.next_egg_id;
    game->game_settings.next_egg_id++;
    return egg;
}