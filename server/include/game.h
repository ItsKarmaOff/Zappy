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
    #include "commands.h"



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

/**
 * @brief Gets a player by their ID
 * @param game The game to get the player from
 * @param player_id The ID of the player to get
 * @return A pointer to the player, or NULL if not found
 */
player_t *get_player_by_id(const game_t *game, size_t player_id);

/**
 * @brief Updates a player in the game
 * @param server The server containing the game
 * @param player The player to update
 * @param dead_players A pointer to a list of dead players
 */
void update_player(server_t *server, player_t *player, node_t **dead_players);

/**
 * @brief Displays a player
 * @param player The player to display
 * @param tab The tab to use for indentation
 */
void display_player(const player_t *player, char *tab);



/* Team functions */

/**
 * @brief Creates a team with the given name
 * @param game The game to create the team in
 * @param name The name of the team
 * @return A pointer to the created team
 */
team_t *create_team(game_t *game, const char *name);

/**
 * @brief Gets the index of a team in the game
 * @param game The game to get the team from
 * @param team_name The name of the team to get the index of
 * @return The index of the team in the game, or 0 if not found
 */
size_t get_team_index(const game_t *game, const char *team_name);

/**
 * @brief Gets the next egg for a team
 * @param server The server containing the game
 * @param team The team to get the next egg for
 * @return A pointer to the next egg, or NULL if no eggs are available
 */
player_t *get_next_egg(server_t *server, team_t *team);

/**
 * @brief Checks if a team name is valid
 * @param server The server containing the game
 * @param team_name The name of the team to check
 * @return true if the team name is valid, false otherwise
 */
bool is_valid_team(server_t *server, char *team_name);

/**
 * @brief Gets the number of players at maximum level in a team
 * @param team The team to check
 * @return The number of players at maximum level in the team
 */
size_t get_number_of_player_level_max_in_team(const team_t *team);

/**
 * @brief Displays a team
 * @param team The team to display
 * @param tab The tab to use for indentation
 */
void display_team(const team_t *team, char *tab);



/* Game functions */

/**
 * @brief Displays a tile
 * @param tile The tile to display
 * @param tab The tab to use for indentation
 */
void display_tile(const tile_t *tile, char *tab);

/**
 * @brief Destroys the game and frees its resources
 * @param game The game to destroy
 */
void destroy_game(game_t *game);

/**
 * @brief Refills the resources in the game
 * @param game The game to refill resources for
 */
void refill_resources(game_t *game);

/**
 * @brief Creates the game map
 * @param game The game to create the map for
 */
void create_game_map(game_t *game);

/**
 * @brief Updates the game
 * @param server The server to update the game on
 */
void update_game(server_t *server);

/**
 * @brief Displays the game
 * @param game The game to display
 */
void display_game(const game_t *game);

#endif /* GAME_H_ */
