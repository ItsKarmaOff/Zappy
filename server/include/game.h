/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The game.h
*/
/**
 * @file game.h
 * @brief The game.h
 * @author Nicolas TORO
 */

#ifndef GAME_H_
    #define GAME_H_

    #include "data_structures.h"

/**
 * @brief Creates a team with the given name
 * @param name The name of the team
 * @return A pointer to the created team
 */
team_t *create_team(const char *name);

/**
 * @brief Updates the game
 * @param server The server to update the game on
 */
void update_game(server_t *server);

#endif /* GAME_H_ */
