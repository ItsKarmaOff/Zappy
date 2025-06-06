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

    #include "server_data_structures.h"



/* Player functions */

/**
 * @brief Creates a player for a team
 * @param game The game to create the player in
 * @param team The team to create the player for
 * @return A pointer to the created player
 */
player_t *create_player(game_t *game, team_t *team);

/**
 * @brief Creates a player from an existing player
 * @param game The game to create the player in
 * @param creator The player to create the new player from
 * @return A pointer to the created player
 */
player_t *create_player_from_player(game_t *game, player_t *creator);



/* Team functions */

/**
 * @brief Creates a team with the given name
 * @param game The game to create the team in
 * @param name The name of the team
 * @return A pointer to the created team
 */
team_t *create_team(game_t *game, const char *name);

/**
 * @brief Gets the number of empty slots in a team
 * @param team The team to check
 * @return The number of empty slots in the team
 */
size_t get_nb_empty_slots(const team_t *team);

/**
 * @brief Gets the index of a team in the game
 * @param game The game to get the team from
 * @param team_name The name of the team to get the index of
 * @return The index of the team in the game, or 0 if not found
 */
size_t get_team_index(const game_t *game, const char *team_name);

/**
 * @brief Gets the next egg for a team
 * @param team The team to get the next egg for
 * @return A pointer to the next egg, or NULL if no eggs are available
 */
player_t *get_next_egg(const team_t *team);



/* Game functions */

/**
 * @brief Destroys the game and frees its resources
 * @param game The game to destroy
 */
void destroy_game(game_t *game);

/**
 * @brief Updates the game
 * @param server The server to update the game on
 */
void update_game(server_t *server);

#endif /* GAME_H_ */
