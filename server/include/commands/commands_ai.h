/*
** EPITECH PROJECT, 2025
** zappy
** File description:
** The commandsai.h
*/
/**
 * @file commands_ai.h
 * @brief The commands_ai.h
 * @author Nicolas TORO
 */

#ifndef COMMANDS_AI_H_
    #define COMMANDS_AI_H_

    #include "network.h"

/**
 * @enum orientation_e
 * @brief The orientation of the player
 */
typedef struct move_s {
    /** The orientation of the player */
    orientation_t orientation;
    /** The function to call to move the player */
    void (*move_func)(const game_t *game, player_t *player);
} move_t;

/**
 * @brief The moves for the AI clients
 */
extern const move_t moves[];



/**
 * @brief Handles the "Forward" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_forward(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Right" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_right(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Left" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_left(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Look" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_look(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Inventory" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_inventory(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Broadcast" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_broadcast(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Connect_nbr" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_connect_nbr(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Fork" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_fork(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Eject" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_eject(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Take" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_take(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Set" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_set(
    server_t *server, client_t *client, char **args);

/**
 * @brief Handles the "Incantation" command for AI clients
 * @param server The server instance
 * @param client The client instance
 * @param args The arguments passed with the command
 */
void handle_ai_command_incantation(
    server_t *server, client_t *client, char **args);

#endif /* COMMANDS_AI_H_ */
