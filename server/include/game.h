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
 * @brief Gets the number of players in a team
 * @param game The game to get the team from
 * @param team The team to get the number of players from
 * @return The number of players in the team
 */
size_t get_nb_players_in_team(const game_t *game, const team_t *team);

/**
 * @brief Gets the index of a team in the game
 * @param game The game to get the team from
 * @param team_name The name of the team to get the index of
 * @return The index of the team in the game, or 0 if not found
 */
size_t get_team_index(const game_t *game, const char *team_name);

/**
 * @brief Creates a player for a team
 * @param team The team to create the player for
 * @return A pointer to the created player
 */
player_t *create_player(team_t *team);

/**
 * @brief Updates the game
 * @param server The server to update the game on
 */
void update_game(server_t *server);

#endif /* GAME_H_ */
